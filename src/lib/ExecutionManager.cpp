#include "ExecutionManager.h"

#include "Executor.h"
#include "ActionManager.h"

#include <QAction>

ExecutionManager::ExecutionManager(ActionManager *actionManager, QObject *parent) :
    QObject(parent),
    actionManager(actionManager),
    isExecuting(false)
{    
    connect(actionManager->getRunAction(),SIGNAL(triggered()),SLOT(startExecuting()));
    connect(actionManager->getWaitAction(),SIGNAL(triggered()),SLOT(stopExecuting()));
}

void ExecutionManager::addExecutor(Executor *executor)
{    
    connect(executor,SIGNAL(finished()),SLOT(executeNext()));
    connect(executor,SIGNAL(error()),SLOT(stopExecuting()));

    executors << executor;
}

void ExecutionManager::startExecuting()
{
    if (!isExecuting) {
        executorsQueue.clear();
        foreach (Executor *executor, executors)
            executorsQueue.enqueue(executor);

        isExecuting = true;
        executeNext();
    }
}

void ExecutionManager::executeNext()
{
    if (isExecuting) {
        if (!executorsQueue.isEmpty()) {
            Executor *executor = executorsQueue.dequeue();
            executor->execute();
        } else {
            stopExecuting();
        }
    }
}

void ExecutionManager::stopExecuting()
{
    if (isExecuting) {
        isExecuting = false;
        actionManager->getWaitAction()->trigger();
    }
}
