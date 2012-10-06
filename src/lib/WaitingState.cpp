#include "WaitingState.h"

#include "ActionManager.h"

#include <QAction>

WaitingState::WaitingState(QObject *parent) :
    PluginState(parent)
{
}

QString WaitingState::getName() const
{
    return tr("Waiting state");
}

void WaitingState::updateActionsAvailability(bool isProjectCanRun)
{
    actionManager->getRunAction()->setEnabled(true & isProjectCanRun);
    actionManager->getRunAction()->setVisible(true);
    actionManager->getWaitAction()->setEnabled(false);
    actionManager->getWaitAction()->setVisible(false);
}

bool WaitingState::isBusy() const
{
    return false;
}
