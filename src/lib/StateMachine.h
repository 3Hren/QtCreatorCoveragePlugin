#pragma once

#include <QObject>

class ActionManager;
class QAction;
class PluginState;
class StateMachine : public QObject
{
    Q_OBJECT
    ActionManager *actionManager;
    PluginState *currentState;
    PluginState *runningState;
    PluginState *waitingState;
public:
    StateMachine(ActionManager *actionManager, QObject *parent = 0);

    void registerRunAction(QAction *runAction);
    void registerWaitAction(QAction *waitAction);

    PluginState *getCurrentState() const;

Q_SIGNALS:
    void stateChanged(PluginState *currentState);
    
private Q_SLOTS:
    void setRunningState();
    void setWaitingState();
    void setState(PluginState *state);

    void updateActionsAvailability();
};
