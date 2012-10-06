#include "Node.h"

#include <QStringList>

#include <QIcon>

#include <QDebug>

Node::Node(const QString &name, Node *parent) :
    name(name),
    parent(parent)
{
    if (parent) {
        if (parent->hasChild(name)) {
            Node *sameNode = parent->getChild(name);
            parent->removeChild(sameNode);
        }

        parent->addChild(this);
    }
}

Node::~Node()
{
    qDeleteAll(children);
    if (parent)
        parent->removeChild(this);
}

QVariant Node::getData() const
{
    return QVariant();
}

QIcon Node::getIcon() const
{
    return QIcon();
}

QString Node::getFullAbsoluteName() const
{
    if (!parent)
        return name;

    return parent->getFullAbsoluteName() + '/' + name;
}

QString Node::getFullName() const
{
    if (!parent)
        return name;

    return parent->getFullName() + '/' + name;
}

QString Node::getName() const
{
    return name;
}

Node *Node::getParent() const
{
    return parent;
}

void Node::addChild(Node *child)
{
    children.append(child);
}

void Node::removeChild(Node *child)
{
    children.removeOne(child);
}

bool Node::hasChild(const QString &name) const
{
    return getChild(name);
}

Node *Node::getChild(const QString &name) const
{
    foreach (Node *child, children) {
        if (child->getName() == name)
            return child;
    }

    return 0;
}

bool Node::hasChildren() const
{
    return !children.isEmpty();
}

QList<Node *> Node::getChildren() const
{
    return children;
}

QList<Node *> Node::findLeafs(const QString &name) const
{
    QList<Node *> leafs;

    if (children.isEmpty() && this->name == name) {
        leafs.append(const_cast<Node *>(this));
        return leafs;
    }

    foreach (Node *child, children)
        leafs << child->findLeafs(name);

    return leafs;
}

QList<Node *> Node::getLeafs() const
{
    QList<Node *> leafs;

    if (!hasChildren()) {
        leafs.append(const_cast<Node *>(this));
        return leafs;
    }

    foreach (Node *child, children)
        leafs.append(child->getLeafs());

    return leafs;
}
