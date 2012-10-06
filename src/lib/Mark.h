#pragma once

#include <texteditor/basetextmark.h>

class MarkManager;
class Mark : public TextEditor::BaseTextMark
{
    MarkManager *manager;
    int type;
public:
    Mark(const QString &fileName, int lineNumber, int type, MarkManager *manager);

    int getType() const;

    void updateLineNumber(int lineNumber);
    void updateBlock(const QTextBlock &block);
    void updateFileName(const QString &fileName);
    void removedFromEditor();
};
