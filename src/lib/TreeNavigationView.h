#pragma once

#include <QTreeView>

class QAbstractItemModel;
class StateMachine;
class PluginState;
class QToolButton;
class QTimer;
class QMovie;
class TreeNavigationView : public QTreeView
{
    Q_OBJECT
    PluginState *state;
    QTimer *animationTimer;
    QMovie *waitingMovie;
public:
    TreeNavigationView(QAbstractItemModel *model, StateMachine *stateMachine, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private Q_SLOTS:
    void setState(PluginState *state);
};
