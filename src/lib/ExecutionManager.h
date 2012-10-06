#pragma once

#include <QObject>
#include <QQueue>

class ActionManager;
class Executor;
class ExecutionManager : public QObject
{
    Q_OBJECT
    ActionManager *actionManager;
    QList<Executor *> executors;
    QQueue<Executor *> executorsQueue;
    bool isExecuting;
public:
    ExecutionManager(ActionManager *actionManager, QObject *parent = 0);    
    
    void addExecutor(Executor *executor);

private Q_SLOTS:
    void startExecuting();
    void executeNext();
    void stopExecuting();
};
