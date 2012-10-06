#include "Model.h"

#include "ProjectTreeManager.h"
#include "Node.h"

#include <QIcon>

#include <QDebug>

Model::Model(ProjectTreeManager *manager, QObject *parent) :
    QAbstractItemModel(parent),
    manager(manager)
{
    connect(manager,SIGNAL(changed()),SLOT(update()));
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Node *parentNode;

    if (!parent.isValid())
        parentNode = manager->getRootNode();
    else
        parentNode = static_cast<Node *>(parent.internalPointer());

    if (row >= 0 && row < parentNode->getChildren().size()) {
        Node *childNode = parentNode->getChildren().value(row);
        return createIndex(row, column, childNode);
    }

    return QModelIndex();
}

QModelIndex Model::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    Node *childNode = static_cast<Node*>(child.internalPointer());
    Node *parentNode = childNode->getParent();

    if (parentNode == manager->getRootNode())
        return QModelIndex();

    Node *grandParentNode = parentNode->getParent();
    int row = -1;
    if (grandParentNode)
        row = grandParentNode->getChildren().indexOf(parentNode);

    if (row == -1)
        return QModelIndex();

    return createIndex(row, 0, parentNode);
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    Node *parentNode = parent.isValid() ? static_cast<Node*>(parent.internalPointer()) : manager->getRootNode();
    return parentNode->getChildren().size();
}

int Model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            if (section == 0)
                return tr("Node");
            if (section == 1)
                return tr("Coverage");
        }
    }

    return QVariant();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    int column(index.column());

    if (!index.isValid())
        return QVariant();

    Node *node = static_cast<Node*>(index.internalPointer());

    if (role == Qt::DisplayRole) {
        if (column == 0)
            return node->getName();
        else if (column == 1)
            return node->getData();
    } else if (role == Qt::DecorationRole) {
        if (column == 0)
            return node->getIcon();
    }

    return QVariant();
}

void Model::update()
{
    reset();
}
