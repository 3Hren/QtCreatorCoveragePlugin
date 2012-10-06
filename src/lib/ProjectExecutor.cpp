#include "ProjectExecutor.h"

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/project.h>
#include <projectexplorer/target.h>
#include "projectexplorer/runconfiguration.h"
#include <projectexplorer/projectconfiguration.h>
#include <projectexplorer/projectnodes.h>
#include <projectexplorer/buildmanager.h>

#include <QDebug>

ProjectExecutor::ProjectExecutor(QObject *parent) :
    Executor(parent)
{
    using namespace ProjectExplorer;
    ProjectExplorerPlugin *projectExplorerPlugin = ProjectExplorerPlugin::instance();
    connect(projectExplorerPlugin->buildManager(),SIGNAL(buildQueueFinished(bool)),SLOT(buildingFinished(bool)));

    connect(projectExplorerPlugin,SIGNAL(runControlFinished(ProjectExplorer::RunControl*)),SIGNAL(finished()));
}

void ProjectExecutor::execute()
{
    using namespace ProjectExplorer;
    ProjectExplorerPlugin *projectExplorerPlugin = ProjectExplorerPlugin::instance();
    Project *startUpProject = projectExplorerPlugin->startupProject();
    Q_ASSERT(startUpProject);

    projectExplorerPlugin->runProject(startUpProject, NormalRunMode);
}

void ProjectExecutor::buildingFinished(bool successfully)
{
    if (!successfully)
        emit error();
}
