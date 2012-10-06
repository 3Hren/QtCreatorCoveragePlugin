#pragma once

#include <QObject>

class Executor : public QObject {
    Q_OBJECT
public:
    Executor(QObject *parent = 0) : QObject(parent) {}

public Q_SLOTS:
    virtual void execute() = 0;

Q_SIGNALS:
    void finished();
    void error();
};
