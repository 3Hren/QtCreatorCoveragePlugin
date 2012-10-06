#include "ProjectNode.h"

#include "IconDecorator.h"

ProjectNode::ProjectNode(const QString &name, const QString &projectFullName, Node *parent) :
    Node(name, parent),
    projectFullName(projectFullName)
{
}

QIcon ProjectNode::getIcon() const
{
    return IconDecorator::getIconByName("Dir.Project");
}

QString ProjectNode::getFullAbsoluteName() const
{
    return projectFullName;
}
