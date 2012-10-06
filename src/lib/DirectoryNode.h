#pragma once

#include "Node.h"

class DirectoryNode : public Node
{    
public:
    DirectoryNode(const QString &name, Node *parent);

    QIcon getIcon() const;
};
