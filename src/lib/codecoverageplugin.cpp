#include "codecoverageplugin.h"
#include "codecoverageconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/modemanager.h>
#include <projectexplorer/projectexplorer.h>

#include <QtPlugin>

#include "ActionManager.h"
#include "StateMachine.h"

#include "ExecutionManager.h"
#include "ProjectExecutor.h"
#include "CleanExecutor.h"
#include "ProcessExecutor.h"
#include "ParserExecutor.h"

#include "ProjectTreeManager.h"
#include "Model.h"
#include "TreeWidgetFactory.h"

#include "Visualizer.h"

#include <QAction>
#include <QDebug>

using namespace CodeCoverage::Internal;

CodeCoveragePlugin::CodeCoveragePlugin()
{
}

CodeCoveragePlugin::~CodeCoveragePlugin()
{
    /*! Unregister objects from the plugin manager's object pool
     *  Delete members
     */
}

bool CodeCoveragePlugin::initialize(const QStringList &arguments, QString *errorString)
{
    /*! Register objects in the plugin manager's object pool
     *  Load settings
     *  Add actions to menus
     *  Connect to other plugins' signals
     *  In the initialize method, a plugin can be sure that the plugins it depends on have initialized their members.
     */
    
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    actionManager = new ActionManager(this);
    stateMachine = new StateMachine(actionManager, this);

    ProjectTreeManager *projectTreeManager = new ProjectTreeManager(this);

    ProjectExecutor *projectExecutor = new ProjectExecutor(this);
    CleanExecutor *coverageCleanExecutor = new CleanExecutor(this);
    ProcessExecutor *coverageProcessExecutor = new ProcessExecutor(this);
    ParserExecutor *parserExecutor = new ParserExecutor(projectTreeManager, this);
    ExecutionManager *executionManager = new ExecutionManager(actionManager, this);    
    executionManager->addExecutor(coverageCleanExecutor);
    executionManager->addExecutor(projectExecutor);        
    executionManager->addExecutor(coverageProcessExecutor);
    executionManager->addExecutor(parserExecutor);

    Model *model = new Model(projectTreeManager, this);
    TreeWidgetFactory *factory = new TreeWidgetFactory(model, stateMachine);
    addAutoReleasedObject(factory);

    Visualizer *visualizer = new Visualizer(projectTreeManager, actionManager->getRenderAction(), this);
    connect(actionManager->getWaitAction(), SIGNAL(triggered()), visualizer, SLOT(renderCoverage()));

    return true;
}

void CodeCoveragePlugin::extensionsInitialized()
{       
    /*! Retrieve objects from the plugin manager's object pool
     *  In the extensionsInitialized method, a plugin can be sure that all
     *  plugins that depend on it are completely initialized.
     */
}

ExtensionSystem::IPlugin::ShutdownFlag CodeCoveragePlugin::aboutToShutdown()
{
    /*! Save settings
     *  Disconnect from signals that are not needed during shutdown
     *  Hide UI (if you add UI that is not in the main window directly)
     */
    return SynchronousShutdown;
}

Q_EXPORT_PLUGIN2(CodeCoverage, CodeCoveragePlugin)

