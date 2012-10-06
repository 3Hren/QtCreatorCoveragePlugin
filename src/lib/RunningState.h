#pragma once

#include "PluginState.h"

class RunningState : public PluginState
{
    Q_OBJECT
public:
    explicit RunningState(QObject *parent = 0);
    
    QString getName() const;
    void updateActionsAvailability(bool isProjectCanRun);

    bool isBusy() const;
};
