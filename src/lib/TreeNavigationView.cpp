#include "TreeNavigationView.h"

#include "StateMachine.h"
#include "PluginState.h"

#include <QHeaderView>
#include <QPainter>
#include <QMovie>
#include <QTimer>

TreeNavigationView::TreeNavigationView(QAbstractItemModel *model, StateMachine *stateMachine, QWidget *parent) :
    QTreeView(parent),
    state(stateMachine->getCurrentState()),
    waitingMovie(new QMovie(this))
{
    setModel(model);
    connect(model,SIGNAL(modelReset()),SLOT(expandAll()));
    header()->resizeSection(0, 200);
    header()->setResizeMode(1, QHeaderView::ResizeToContents);

    setFrameStyle(QFrame::Plain);
    setFrameShape(QFrame::NoFrame);
    setContentsMargins(0, 0, 0, 0);

    connect(stateMachine,SIGNAL(stateChanged(PluginState*)),SLOT(setState(PluginState*)));

    waitingMovie->setFileName(":/animation/images/loading.gif");
    animationTimer = new QTimer(this);
    connect(animationTimer,SIGNAL(timeout()),viewport(),SLOT(repaint()));
}

void TreeNavigationView::paintEvent(QPaintEvent *event)
{
    if (state->isBusy()) {
        QPainter painter(viewport());
        QSize size(50, 50);
        QPoint center = viewport()->rect().center();
        QRect rect(center.x() - size.width() / 2, center.y() - size.height() / 2, size.width(), size.height());
        painter.drawPixmap(rect, waitingMovie->currentPixmap());
    } else
        QTreeView::paintEvent(event);
}

void TreeNavigationView::setState(PluginState *state)
{
    if (this->state != state) {
        this->state = state;

        if (state->isBusy()) {
            waitingMovie->start();
            animationTimer->start();
        } else {
            waitingMovie->stop();
            animationTimer->stop();
        }
    }
}
