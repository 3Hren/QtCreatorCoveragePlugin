SOURCES += codecoverageplugin.cpp \
    RunningState.cpp \
    WaitingState.cpp \
    Node.cpp \
    RootNode.cpp \
    ProjectNode.cpp \
    FileNode.cpp \
    ActionManager.cpp \
    ProjectExecutor.cpp \
    ExecutionManager.cpp \
    TreeCreator.cpp \
    ProjectTreeManager.cpp \
    ProjectTreeFiller.cpp \
    ProjectTreeCreator.cpp \
    ParserExecutor.cpp \
    StateMachine.cpp \
    CleanExecutor.cpp \
    Model.cpp \
    Parser.cpp \
    ProcessExecutor.cpp \
    TreeWidgetFactory.cpp \
    DirectoryNode.cpp \
    IconDecorator.cpp \
    TreeNavigationView.cpp \
    PluginState.cpp \
    Mark.cpp \
    MarkManager.cpp \
    Visualizer.cpp \
    LinePainter.cpp \
    LinePaintHandler.cpp \
    LineCleaner.cpp

HEADERS += codecoverageplugin.h\
    codecoverage_global.h\
    codecoverageconstants.h \
    RunningState.h \
    WaitingState.h \
    Node.h \
    RootNode.h \
    ProjectNode.h \
    FileCoverageData.h \
    FileNode.h \
    ActionManager.h \
    ProjectExecutor.h \
    ExecutionManager.h \
    Executor.h \
    TreeCreator.h \
    ProjectTreeManager.h \
    ProjectTreeFiller.h \
    ProjectTreeCreator.h \
    ParserExecutor.h \
    TreeWidgetFactory.h \
    ProcessExecutor.h \
    Parser.h \
    CleanExecutor.h \
    StateMachine.h \
    Model.h \
    DirectoryNode.h \
    IconDecorator.h \
    TreeNavigationView.h \
    PluginState.h \
    Mark.h \
    MarkManager.h \
    Visualizer.h \
    LinePainter.h \
    LinePaintHandler.h \
    LineCleaner.h

include(codecoverage_dependencies.pri)

FORMS +=

RESOURCES += \
    resources.qrc
