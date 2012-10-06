#pragma once

#include <QString>
#include <QStringList>

class Node;
class TreeCreator
{
    QStringList fileNames;
    Node *rootNode;
public:
    TreeCreator(const QString &fileName, Node *rootNode = 0);
    TreeCreator(const QStringList &fileNames, Node *rootNode = 0);

    void execute();

    Node *getRootNode() const;
};
