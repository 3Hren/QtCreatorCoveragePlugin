#pragma once

#include "Executor.h"

class ProjectTreeManager;
class ParserExecutor : public Executor
{
    Q_OBJECT
    ProjectTreeManager *projectTreeManager;
public:
    ParserExecutor(ProjectTreeManager *projectTreeManager, QObject *parent = 0);
    
public Q_SLOTS:
    void execute();
    
};
