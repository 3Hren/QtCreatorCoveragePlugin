#pragma once

#include "Node.h"
#include "FileCoverageData.h"

class FileNode : public Node
{
    LineHitList lineHitList;
public:
    FileNode(const QString &name, Node *parent);

    QVariant getData() const;
    QIcon getIcon() const;

    LineHitList getLineHitList() const;
    void setLineHitList(const LineHitList &lineHitList);
};

