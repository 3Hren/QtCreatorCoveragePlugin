#include "Mark.h"

#include "MarkManager.h"

Mark::Mark(const QString &fileName, int lineNumber, int type, MarkManager *manager) :
    BaseTextMark(fileName, lineNumber),
    manager(manager),
    type(type)
{
    setPriority(TextEditor::ITextMark::NormalPriority);
    QIcon icon = type != 0 ? QIcon(":/icons/images/plus.png") : QIcon(":/icons/images/minus.png");
    setIcon(icon);
}

int Mark::getType() const
{
    return type;
}

void Mark::updateLineNumber(int lineNumber)
{
    BaseTextMark::updateLineNumber(lineNumber);
}

void Mark::updateBlock(const QTextBlock &block)
{
    BaseTextMark::updateBlock(block);
}

void Mark::updateFileName(const QString &fileName)
{
    BaseTextMark::updateFileName(fileName);
}

void Mark::removedFromEditor()
{
    BaseTextMark::removedFromEditor();
}
