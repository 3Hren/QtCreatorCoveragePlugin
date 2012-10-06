#pragma once

#include "Executor.h"
#include "ProcessExecutor.h"

class CleanExecutor : public ProcessExecutor
{
    Q_OBJECT
public:
    explicit CleanExecutor(QObject *parent = 0);
    
public Q_SLOTS:
    void execute();
};
