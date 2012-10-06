#include "StateMachine.h"

#include "ActionManager.h"

#include "RunningState.h"
#include "WaitingState.h"

#include <projectexplorer/projectexplorer.h>

#include <QAction>

#include <QDebug>

StateMachine::StateMachine(ActionManager *actionManager, QObject *parent) :
    QObject(parent),
    actionManager(actionManager),
    currentState(0),
    runningState(new RunningState(this)),
    waitingState(new WaitingState(this))
{
    runningState->setActionManager(actionManager);
    waitingState->setActionManager(actionManager);

    registerRunAction(actionManager->getRunAction());
    registerWaitAction(actionManager->getWaitAction());
    setWaitingState();

    ProjectExplorer::ProjectExplorerPlugin *projectExplorerPlugin = ProjectExplorer::ProjectExplorerPlugin::instance();
    connect(projectExplorerPlugin,SIGNAL(updateRunActions()),SLOT(updateActionsAvailability()));
}

void StateMachine::registerRunAction(QAction *runAction)
{
    connect(runAction,SIGNAL(triggered()),SLOT(setRunningState()));
}

void StateMachine::registerWaitAction(QAction *waitAction)
{
    connect(waitAction,SIGNAL(triggered()),SLOT(setWaitingState()));
}

PluginState *StateMachine::getCurrentState() const
{
    return currentState;
}

void StateMachine::setRunningState()
{
    setState(runningState);
}

void StateMachine::setWaitingState()
{
    setState(waitingState);
}

void StateMachine::setState(PluginState *state)
{
    if (currentState != state) {
        currentState = state;        
        updateActionsAvailability();
        emit stateChanged(currentState);
    }
}

void StateMachine::updateActionsAvailability()
{
    using namespace ProjectExplorer;
    ProjectExplorerPlugin *projectExplorerPlugin = ProjectExplorerPlugin::instance();
    Project *project = projectExplorerPlugin->startupProject();
    const bool isProjectCanRun = projectExplorerPlugin->canRun(project, NormalRunMode);

    currentState->updateActionsAvailability(isProjectCanRun);
}
