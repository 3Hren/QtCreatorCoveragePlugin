#include "ProjectTreeManager.h"

#include "ProjectTreeFiller.h"
#include "RootNode.h"

ProjectTreeManager::ProjectTreeManager(QObject *parent) :
    QObject(parent),
    rootNode(new RootNode)
{
}

void ProjectTreeManager::addProject(const QString &projectName, const FileCoverageDataList &fileCoverageDataList)
{
    ProjectTreeFiller filler(projectName, fileCoverageDataList, rootNode);
    filler.execute();
    emit changed();
}

Node *ProjectTreeManager::getRootNode() const
{
    return rootNode;
}
