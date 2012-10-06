#include "LinePainter.h"

LinePainter::LinePainter(QPlainTextEdit *textEdit, const QMap<int, int> &lineCoverage) :
    LinePaintHandler(textEdit, lineCoverage)
{
}

QColor LinePainter::getColorForValue(int value) const
{
    const QColor green(0, 255, 0, 20);
    const QColor red(255, 0, 0, 20);
    return value > 0 ? green : red;
}
