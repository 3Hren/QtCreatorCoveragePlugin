#pragma once

#include "Executor.h"

namespace ProjectExplorer {
class RunControl;
}

class WizardManager;
class ProjectExecutor : public Executor
{
    Q_OBJECT
public:
    explicit ProjectExecutor(QObject *parent = 0);

public Q_SLOTS:
    void execute();

private Q_SLOTS:
    void buildingFinished(bool successfully);
};
