#pragma once

#include <QAbstractItemModel>

class ProjectTreeManager;
class Model : public QAbstractItemModel
{
    Q_OBJECT
    ProjectTreeManager *manager;
public:
    Model(ProjectTreeManager *manager, QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private Q_SLOTS:
    void update();
};
