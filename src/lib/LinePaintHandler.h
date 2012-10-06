#pragma once

#include <QMap>
#include <QColor>

class QPlainTextEdit;
class LinePaintHandler
{
    QPlainTextEdit *textEdit;
    QMap<int, int> lineCoverage;
public:
    LinePaintHandler(QPlainTextEdit *textEdit, const QMap<int, int> &lineCoverage);
    virtual ~LinePaintHandler();

    void render();
protected:
    virtual QColor getColorForValue(int value) const = 0;
};
