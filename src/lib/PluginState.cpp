#include "PluginState.h"

#include <projectexplorer/projectexplorer.h>

#include <QDebug>

PluginState::PluginState(QObject *parent) :
    QObject(parent)
{    
}

void PluginState::setActionManager(ActionManager *actionManager)
{
    this->actionManager = actionManager;
}
