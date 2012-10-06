#pragma once

#include "Node.h"

#include <QString>

class RootNode;
class ProjectNode : public Node
{
    QString projectFullName;
public:
    ProjectNode(const QString &name, const QString &projectFullName, Node *parent);

    QIcon getIcon() const;

    QString getFullAbsoluteName() const;
};
