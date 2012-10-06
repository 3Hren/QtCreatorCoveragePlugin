#include "ActionManager.h"

#include "codecoverageconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/modemanager.h>

#include <QMenu>
#include <QAction>

ActionManager::ActionManager(QObject *parent) :
    QObject(parent),
    runAction(new QAction(QIcon(":/icons/images/run.png"), tr("Run tests"), this)),
    waitAction(new QAction(QIcon(":/icons/images/stop.png"), tr("Stop coverage execution"), this)),
    renderAction(new QAction(QIcon(":/icons/images/render.png"), tr("Show code coverage"), this))
{
    renderAction->setCheckable(true);

    // Add action to menu
    Core::ActionManager *pluginActionManager = Core::ICore::actionManager();           
    Core::Command *runCommand = pluginActionManager->registerAction(runAction, RUN_ACTION_ID, Core::Context(Core::Constants::C_GLOBAL));
    Core::Command *renderCommand = pluginActionManager->registerAction(renderAction, RENDER_ACTION_ID, Core::Context(Core::Constants::C_GLOBAL));
    runCommand->setKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_E);
    renderCommand->setKeySequence(Qt::CTRL + Qt::Key_H);

    Core::ActionContainer *menu = pluginActionManager->createMenu(MENU_ID);
    menu->menu()->setTitle(tr("CodeCoverage"));
    menu->addAction(runCommand);    
    menu->addAction(renderCommand);
    pluginActionManager->actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    // Add action as icon to left bar
    Core::ModeManager *modeManager = Core::ModeManager::instance();
    modeManager->addAction(runAction, RUN_ACTION_PRIORITY);
    modeManager->addAction(waitAction, WAIT_ACTION_PRIORITY);
}

QAction *ActionManager::getRunAction() const
{
    return runAction;
}

QAction *ActionManager::getWaitAction() const
{
    return waitAction;
}

QAction *ActionManager::getRenderAction() const
{
    return renderAction;
}
