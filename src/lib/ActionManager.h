#pragma once

#include <QObject>

class QAction;
class ActionManager : public QObject
{
    Q_OBJECT
    QAction *runAction;
    QAction *waitAction;
    QAction *renderAction;
public:
    explicit ActionManager(QObject *parent = 0);

    QAction *getRunAction() const;
    QAction *getWaitAction() const;
    QAction *getRenderAction() const;
};
