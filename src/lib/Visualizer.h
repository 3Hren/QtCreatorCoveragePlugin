#pragma once

#include <QObject>
#include <QMap>

namespace Core {class IEditor;}
namespace TextEditor {class ITextEditor;}

class ProjectTreeManager;
class MarkManager;
class QAction;
class QPlainTextEdit;
class Visualizer : public QObject
{
    Q_OBJECT
    ProjectTreeManager *projectTreeManager;
    MarkManager *markManager;
    QAction *renderAction;
public:
    Visualizer(ProjectTreeManager *projectTreeManager, QAction *renderAction, QObject *parent = 0);

public Q_SLOTS:
    void refreshMarks();
    void renderCoverage();

private Q_SLOTS:
    void renderCoverage(QPlainTextEdit *plainTextEdit) const;
    void clearCoverage(QPlainTextEdit *plainTextEdit) const;
    void bindEditorToPainting(Core::IEditor *editor);

    void repaintMarks(bool isRender);

private:
    TextEditor::ITextEditor *currentTextEditor() const;
    QMap<int, int> getLineCoverage() const;
    
};
