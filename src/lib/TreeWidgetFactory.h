#pragma once

#include <coreplugin/inavigationwidgetfactory.h>

class Model;
class StateMachine;
class TreeWidgetFactory : public Core::INavigationWidgetFactory
{
    Model *model;
    StateMachine *stateMachine;
public:    
    TreeWidgetFactory(Model *model, StateMachine *stateMachine);

    QString displayName() const;
    int priority() const;
    Core::Id id() const;
    Core::NavigationView createWidget();
};
