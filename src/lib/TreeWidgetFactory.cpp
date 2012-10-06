#include "TreeWidgetFactory.h"

#include "Model.h"
#include "TreeNavigationView.h"

TreeWidgetFactory::TreeWidgetFactory(Model *model, StateMachine *stateMachine) :
    model(model),
    stateMachine(stateMachine)
{
}

QString TreeWidgetFactory::displayName() const
{
    return tr("Coverage");
}

int TreeWidgetFactory::priority() const
{
    return 110;
}

Core::Id TreeWidgetFactory::id() const
{
    return Core::Id("Coverage");
}

Core::NavigationView TreeWidgetFactory::createWidget()
{
    Core::NavigationView n;
    TreeNavigationView *navigationView = new TreeNavigationView(model, stateMachine);
    n.widget = navigationView;
    return n;
}
