#pragma once

#include <QObject>

class ActionManager;
class PluginState : public QObject
{
    Q_OBJECT
protected:
    ActionManager *actionManager;

public:
    explicit PluginState(QObject *parent = 0);

    void setActionManager(ActionManager *actionManager);

    virtual QString getName() const = 0;   
    virtual void updateActionsAvailability(bool isProjectCanRun) = 0;

    virtual bool isBusy() const = 0;
};
