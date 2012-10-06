#pragma once

#include "PluginState.h"

class WaitingState : public PluginState
{
    Q_OBJECT
public:
    explicit WaitingState(QObject *parent = 0);

    QString getName() const;
    void updateActionsAvailability(bool isProjectCanRun);

    bool isBusy() const;
};
