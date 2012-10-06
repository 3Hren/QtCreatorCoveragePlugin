#pragma once

#include "FileCoverageData.h"

class Node;
class ProjectTreeFiller
{
    const QString projectName;
    FileCoverageDataList fileCoverageDataList;
    Node *rootNode;
public:
    ProjectTreeFiller(const QString &projectName, const FileCoverageDataList &fileCoverageDataList, Node *rootNode);

    void execute();
};
