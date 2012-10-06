#include "ProcessExecutor.h"

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/project.h>
#include <projectexplorer/target.h>
#include <projectexplorer/projectnodes.h>
#include <projectexplorer/runconfiguration.h>

#include <QDebug>

ProcessExecutor::ProcessExecutor(QObject *parent) :
    Executor(parent),
    process(new QProcess(this))
{
    connect(process,SIGNAL(readyReadStandardOutput()),SLOT(readOutput()));
    connect(process,SIGNAL(readyReadStandardError()),SLOT(readError()));
    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),SLOT(handleCoverageResults(int,QProcess::ExitStatus)));
}

void ProcessExecutor::execute()
{
    using namespace ProjectExplorer;

    ProjectExplorerPlugin *projectExplorerPlugin = ProjectExplorerPlugin::instance();
    Project *project = projectExplorerPlugin->startupProject();

    ProjectNode *rootProjectNode = project->rootProjectNode();
    const QString &activeRunConfigurationDir = getRunConfigurationPath(rootProjectNode, project->activeTarget()->activeRunConfiguration());

    const QString &buildDir = activeRunConfigurationDir.mid(0, activeRunConfigurationDir.lastIndexOf('/'));
    const QString &objectFilesDir = getObjectFilesDir(buildDir);

    const QString &rootDir = project->projectDirectory();
    QDir dir(rootDir);
    dir.mkdir("./coverage");
    const QString outputFileName = rootDir + '/' + "coverage/result.info";

    const QString program = "lcov";
    const QStringList arguments = {
        "-d",
        objectFilesDir,
        "-c",
        "-o",
        outputFileName,
        "-b",
        buildDir
    };

    process->start(program, arguments);
}

void ProcessExecutor::readOutput()
{
}

void ProcessExecutor::readError()
{
}

void ProcessExecutor::handleCoverageResults(int code, QProcess::ExitStatus exitStatus)
{    
    if (code == 0 && exitStatus == QProcess::NormalExit)
        emit finished();
    else
        emit error();
}

//#TOTEST:
QString ProcessExecutor::getRunConfigurationPath(ProjectExplorer::ProjectNode *parent, ProjectExplorer::RunConfiguration *activeRunConfiguration) const
{
    using namespace ProjectExplorer;

    foreach (ProjectNode *projectNode, parent->subProjectNodes()) {
        foreach (RunConfiguration *runConfiguration, projectNode->runConfigurationsFor(projectNode))
            if (runConfiguration == activeRunConfiguration)
                return projectNode->path();

        const QString &runConfigurationPath = getRunConfigurationPath(projectNode, activeRunConfiguration);
        if (!runConfigurationPath.isEmpty())
            return runConfigurationPath;
    }

    return QString();
}

//#TOTEST:
QString ProcessExecutor::getObjectFilesDir(const QString &buildDir) const
{
    QFile makeFile(buildDir + "/Makefile");
    QTextStream out(&makeFile);

    if (makeFile.open(QIODevice::ReadOnly)) {
        while (!out.atEnd()) {
            const QString &line = out.readLine();

            QRegExp rx("OBJECTS_DIR\\s*=\\s*([^\\s]*)$");
            if (rx.indexIn(line) != -1) {
                const QString &objectsDir = rx.cap(1);
                return QString("%1/%2").arg(buildDir).arg(objectsDir);
            }
        }
    }

    return buildDir;
}
