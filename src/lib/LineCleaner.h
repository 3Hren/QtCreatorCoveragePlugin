#pragma once

#include "LinePaintHandler.h"

class LineCleaner : public LinePaintHandler
{
public:
    LineCleaner(QPlainTextEdit *textEdit, const QMap<int, int> &lineCoverage);

protected:
    QColor getColorForValue(int value) const;
};
