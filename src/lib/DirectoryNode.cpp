#include "DirectoryNode.h"

#include "IconDecorator.h"

DirectoryNode::DirectoryNode(const QString &name, Node *parent) :
    Node(name, parent)
{
}

QIcon DirectoryNode::getIcon() const
{
    const QString &name = getName();
    if (name == "Headers")
        return IconDecorator::getIconByName("Dir.Headers");
    if (name == "Sources")
        return IconDecorator::getIconByName("Dir.Sources");

    return IconDecorator::getIconByName("Dir.Other");
}
