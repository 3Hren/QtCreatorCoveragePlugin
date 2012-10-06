#include "MarkManager.h"

#include "Mark.h"

MarkManager::MarkManager(QObject *parent) :
    QObject(parent)
{
}

MarkManager::~MarkManager()
{
    removeAllMarks();
}

void MarkManager::removeAllMarks()
{
    qDeleteAll(marks);
    marks.clear();
}

void MarkManager::addMark(const QString &fileName, int lineNumber, int type)
{
    Mark *mark = new Mark(fileName, lineNumber, type, this);
    marks.insert(fileName, mark);
    mark->init();
}
