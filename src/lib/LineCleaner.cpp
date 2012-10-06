#include "LineCleaner.h"

LineCleaner::LineCleaner(QPlainTextEdit *textEdit, const QMap<int, int> &lineCoverage) :
    LinePaintHandler(textEdit, lineCoverage)
{
}

QColor LineCleaner::getColorForValue(int value) const
{
    Q_UNUSED(value);
    return QColor(Qt::white);
}
