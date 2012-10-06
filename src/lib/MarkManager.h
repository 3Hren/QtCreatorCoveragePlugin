#pragma once

#include <QObject>

#include <QMultiHash>

class Mark;
class MarkManager : public QObject
{
    Q_OBJECT
    QMultiHash<QString, Mark *> marks;
public:
    explicit MarkManager(QObject *parent = 0);
    ~MarkManager();

    void removeAllMarks();

    void addMark(const QString &fileName, int lineNumber, int type);
};
