#include "RunningState.h"

#include "ActionManager.h"

#include <QAction>

#include <QDebug>

RunningState::RunningState(QObject *parent) :
    PluginState(parent)
{
}

QString RunningState::getName() const
{
    return tr("Running state");
}

void RunningState::updateActionsAvailability(bool isProjectCanRun)
{
    actionManager->getRunAction()->setEnabled(false);
    actionManager->getRunAction()->setVisible(false);
    actionManager->getWaitAction()->setEnabled(true & isProjectCanRun);
    actionManager->getWaitAction()->setVisible(true);
}

bool RunningState::isBusy() const
{
    return true;
}
