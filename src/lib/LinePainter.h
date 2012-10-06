#pragma once

#include "LinePaintHandler.h"

class LinePainter : public LinePaintHandler
{
public:
    LinePainter(QPlainTextEdit *textEdit, const QMap<int, int> &lineCoverage);

protected:
    QColor getColorForValue(int value) const;
};
