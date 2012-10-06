#include "TreeCreator.h"

#include "DirectoryNode.h"
#include "FileNode.h"

#include <QStringList>
#include <QDebug>

TreeCreator::TreeCreator(const QString &fileName, Node *rootNode) :
    fileNames(fileName),
    rootNode(rootNode ? rootNode : new Node())
{
}

TreeCreator::TreeCreator(const QStringList &fileNames, Node *rootNode) :
    fileNames(fileNames),
    rootNode(rootNode ? rootNode : new Node())
{
}

void TreeCreator::execute()
{            
    foreach (const QString &fileName, fileNames) {
        QStringList nodeNames = fileName.split('/', QString::SkipEmptyParts);
        const QString &leafName = nodeNames.takeLast();

        Node *parentNode = rootNode;
        while (!nodeNames.isEmpty()) {
            QString nodeName = nodeNames.takeFirst();
            parentNode = parentNode->hasChild(nodeName) ? parentNode->getChild(nodeName) : new DirectoryNode(nodeName, parentNode);
        }

        Node *leafNode = new FileNode(leafName, parentNode);
        Q_UNUSED(leafNode);
    }
}

Node *TreeCreator::getRootNode() const
{
    return rootNode;
}
