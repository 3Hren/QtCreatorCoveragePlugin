#include "CleanExecutor.h"

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/project.h>
#include <projectexplorer/target.h>
#include <projectexplorer/projectnodes.h>
#include <projectexplorer/runconfiguration.h>

#include <QDebug>

CleanExecutor::CleanExecutor(QObject *parent) :
    ProcessExecutor(parent)
{
}

void CleanExecutor::execute()
{
    using namespace ProjectExplorer;

    ProjectExplorerPlugin *projectExplorerPlugin = ProjectExplorerPlugin::instance();
    Project *project = projectExplorerPlugin->startupProject();

    ProjectNode *rootProjectNode = project->rootProjectNode();
    const QString &activeRunConfigurationDir = getRunConfigurationPath(rootProjectNode, project->activeTarget()->activeRunConfiguration());

    const QString &buildDir = activeRunConfigurationDir.mid(0, activeRunConfigurationDir.lastIndexOf('/'));
    const QString &objectFilesDir = getObjectFilesDir(buildDir);

    const QString program = "lcov";
    const QStringList arguments = {
        "-z",
        "-d",
        objectFilesDir
    };

    process->start(program, arguments);
}
