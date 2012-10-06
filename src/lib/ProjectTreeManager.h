#pragma once

#include <QObject>

#include "FileCoverageData.h"

#include <QString>

class Node;
class ProjectTreeManager : public QObject
{
    Q_OBJECT
    Node *rootNode;
public:
    ProjectTreeManager(QObject *parent = 0);

    void addProject(const QString &projectName, const FileCoverageDataList &fileCoverageDataList);

    Node *getRootNode() const;

Q_SIGNALS:
    void changed();
};
