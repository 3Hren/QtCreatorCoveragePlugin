#pragma once

#include <QString>
#include <QStringList>
#include <QMultiHash>

class Node;
class TreeCreator;
class ProjectTreeCreator
{
    Node *rootNode;
    QStringList fileNames;
public:
    ProjectTreeCreator(const QStringList &fileNames, Node *rootNode = 0);

    void execute();

    Node *getRootNode() const;
    Node *getLeafNodeFromFullName(const QString &fullName, const QString &prefix = QString()) const;

private:
    QString getFileNameWithProjectSpecialDirectory(const QString &fileName) const;
    QStringList getFileNamesWithProjectSpecialDirectory() const;

    static QMultiHash<QString, QString> SpecialDirectoryTable();
};
