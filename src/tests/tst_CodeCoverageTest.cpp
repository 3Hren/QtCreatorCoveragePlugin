#include <QString>
#include <QtTest>

#include "RunAction.h"
#include "WaitAction.h"
#include "CodeCoverageStateMachine.h"
#include "states/CodeCoverageState.h"
#include "processes/CodeCoverageMockProcess.h"
#include "CodeCoverageProcessor.h"
#include "exceptions/CodeCoverageProcessorException.h"

#define QVERIFY_THROW(expression, ExpectedExceptionType) \
    do { \
    bool caught = false; \
    try { expression; } \
    catch (ExpectedExceptionType const &) { caught = true; } \
    catch (...) {} \
    QVERIFY2(caught, "expecting " #expression " to throw <" #ExpectedExceptionType ">"); \
    } while(0)

class CodeCoverageTest : public QObject
{
    Q_OBJECT
    
public:
    CodeCoverageTest();
    
private Q_SLOTS:
    void testStateMachineSwitchingStateByActions();
    void testStateMachineNotSwitchStateIfItAlreadyInThisState();
    void testRunnerStartingAndFinishing();
    void testRunnerWrongObjectFilesDir();
    void testRunnerWrongBaseDir();
    void testRunnerWrongOutputDir();
    void testNodeFindChildByName();
    void testNodeHasChildByName();
    void testFindLeafs();
    void testGetFullName();
    void testFindManyLeafsWithSameName();
    void testCreateTreeFromString();
    void testCreateTreeFromStringList();
    void testFileIsLeaf();
    void testCreateProjectTree();
    void testGetHeaderLeafNodeFromFullName();
    void testGetSourceLeafNodeFromFullName();
    void testCoverageInformationParser();
    void testCoverateInformationParserNonExistingFileName();
    void testProjectTreeCreator();
    //! In fact next four tests are unnecessary because they were passed without code refactoring.
    void testProjectTreeCreatorMoreThanOneProject();
    void testProjectTreeCreatorDublicateProject();
    void testProjectTreeCreatorSameProjectWillReplaceOldOne();
    void testProjectTreeCreatorSameProjectWithAddedFiles();
    void testCodeCoverageModelRowCount();
    void testCodeCoverageModelColumnCount();
};

CodeCoverageTest::CodeCoverageTest()
{
}

Q_DECLARE_METATYPE(CodeCoverageState *)
void CodeCoverageTest::testStateMachineSwitchingStateByActions()
{
    RunAction rA;
    WaitAction wA;
    CodeCoverageStateMachine sM;
    sM.registerRunAction(&rA);
    sM.registerWaitAction(&wA);
    qRegisterMetaType<CodeCoverageState*>();
    QSignalSpy spy(&sM, SIGNAL(stateChanged(CodeCoverageState*)));

    rA.trigger();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(sM.getCurrentState()->getName(), QString("Running state"));

    wA.trigger();
    QCOMPARE(spy.count(), 2);
    QCOMPARE(sM.getCurrentState()->getName(), QString("Waiting state"));

    rA.trigger();
    QCOMPARE(spy.count(), 3);
    QCOMPARE(sM.getCurrentState()->getName(), QString("Running state"));
}

void CodeCoverageTest::testStateMachineNotSwitchStateIfItAlreadyInThisState()
{
    RunAction rA;
    WaitAction wA;
    CodeCoverageStateMachine sM;
    sM.registerRunAction(&rA);
    sM.registerWaitAction(&wA);
    qRegisterMetaType<CodeCoverageState*>();
    QSignalSpy spy(&sM, SIGNAL(stateChanged(CodeCoverageState*)));

    wA.trigger();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(sM.getCurrentState()->getName(), QString("Waiting state"));

    wA.trigger();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(sM.getCurrentState()->getName(), QString("Waiting state"));
}

void CodeCoverageTest::testRunnerStartingAndFinishing()
{
    CodeCoverageMockProcess mockProcess;
    CodeCoverageProcessor cCP(&mockProcess);
    QSignalSpy startSpy(&mockProcess,SIGNAL(started()));
    QSignalSpy finishSpy(&mockProcess,SIGNAL(finished(int)));
    cCP.setObjectFilesDir(QString("%1/base/objects").arg(TEST_DIR));
    cCP.setBaseDir(QString("%1/base").arg(TEST_DIR));
    cCP.setOutputDir(QString("%1/output").arg(TEST_DIR));

    cCP.execute();

    QCOMPARE(startSpy.count(), 1);
    QCOMPARE(finishSpy.count(), 1);
    QCOMPARE(finishSpy.takeFirst().at(0).toInt(), 0);
}

void CodeCoverageTest::testRunnerWrongObjectFilesDir()
{
    CodeCoverageMockProcess mockProcess;
    CodeCoverageProcessor cCP(&mockProcess);
    QSignalSpy spy(&mockProcess,SIGNAL(finished(int)));
    cCP.setObjectFilesDir(QString("%1/").arg(TEST_DIR));
    cCP.setBaseDir(QString("%1/base").arg(TEST_DIR));
    cCP.setOutputDir(QString("%1/output").arg(TEST_DIR));

    cCP.execute();

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.takeFirst().at(0).toInt(), 1);
}

void CodeCoverageTest::testRunnerWrongBaseDir()
{
    CodeCoverageMockProcess mockProcess;
    CodeCoverageProcessor cCP(&mockProcess);
    QSignalSpy finishSpy(&mockProcess,SIGNAL(finished(int)));
    cCP.setObjectFilesDir(QString("%1/base/objects").arg(TEST_DIR));
    cCP.setBaseDir(QString("%1/").arg(TEST_DIR));
    cCP.setOutputDir(QString("%1/output").arg(TEST_DIR));

    cCP.execute();

    QCOMPARE(finishSpy.count(), 1);
    QCOMPARE(finishSpy.takeFirst().at(0).toInt(), 2);
}

void CodeCoverageTest::testRunnerWrongOutputDir()
{
    CodeCoverageMockProcess mockProcess;
    CodeCoverageProcessor cCP(&mockProcess);
    QSignalSpy finishSpy(&mockProcess,SIGNAL(finished(int)));
    cCP.setObjectFilesDir(QString("%1/base/objects").arg(TEST_DIR));
    cCP.setBaseDir(QString("%1/base").arg(TEST_DIR));
    cCP.setOutputDir(QString("%1/NotExistingDir").arg(TEST_DIR));

    cCP.execute();

    QCOMPARE(finishSpy.count(), 1);
    QCOMPARE(finishSpy.takeFirst().at(0).toInt(), 4);
}

#include "nodes/Node.h"
#include "nodes/RootNode.h"
#include "nodes/ProjectNode.h"

void CodeCoverageTest::testNodeFindChildByName()
{
    RootNode *rootNode = new RootNode();
    Node *projectNode = new ProjectNode("ProjectName", rootNode);

    QCOMPARE(rootNode->getChild("ProjectName"), projectNode);

    delete projectNode;
    delete rootNode;
}

void CodeCoverageTest::testNodeHasChildByName()
{
    RootNode *rootNode = new RootNode();
    Node *projectNode = new ProjectNode("ProjectName", rootNode);
    Q_UNUSED(projectNode);

    QCOMPARE(rootNode->hasChild("ProjectName"), true);

    delete rootNode;
}

void CodeCoverageTest::testFindLeafs()
{
    RootNode *rootNode = new RootNode();
    Node *projectNode = new ProjectNode("ProjectName", rootNode);
    Node *fileNode = new Node("filename.cpp", projectNode);

    QCOMPARE(rootNode->findLeafs("filename.cpp").size(), 1);
    QCOMPARE(fileNode->findLeafs("filename.cpp").at(0), fileNode);
}

void CodeCoverageTest::testGetFullName()
{
    RootNode *rootNode = new RootNode();
    Node *projectNode = new ProjectNode("ProjectName", rootNode);
    Node *fileNode = new Node("filename.cpp", projectNode);

    QCOMPARE(fileNode->getFullName(), QString("/ProjectName/filename.cpp"));
}

void CodeCoverageTest::testFindManyLeafsWithSameName()
{
    RootNode *rootNode = new RootNode();
    Node *firstProjectNode = new ProjectNode("ProjectName_1", rootNode);
    Node *secondProjectNode = new ProjectNode("ProjectName_2", rootNode);
    Node *firstFileNode = new Node("filename.cpp", firstProjectNode);
    Node *secondFileNode = new Node("filename.cpp", secondProjectNode);

    QCOMPARE(rootNode->findLeafs("filename.cpp").size(), 2);
    QCOMPARE(rootNode->findLeafs("filename.cpp").contains(firstFileNode), QBool(true));
    QCOMPARE(rootNode->findLeafs("filename.cpp").contains(secondFileNode), QBool(true));
}

#include "tree/TreeCreator.h"
void CodeCoverageTest::testCreateTreeFromString()
{
    QString fileName("Dir/Project/src/filename.ext");
    TreeCreator tC(fileName);
    tC.execute();

    Node *rootNode = tC.getRootNode();

    QCOMPARE(rootNode->hasChild("Dir"), true);
    QCOMPARE(rootNode->getChild("Dir")->hasChild("Project"), true);
    QCOMPARE(rootNode->getChild("Dir")->getChild("Project")->hasChild("src"), true);
    QCOMPARE(rootNode->getChild("Dir")->getChild("Project")->getChild("src")->hasChild("filename.ext"), true);
}

void TREE_RECURSIVE_NODE_COMPARE(Node *rootNode, const QString &nodeItemsString) {
    QStringList nodeItems = nodeItemsString.split('/');
    Node *currentNode = rootNode;
    while (!nodeItems.isEmpty()) {
        QString nodeName = nodeItems.takeFirst();
        QCOMPARE(currentNode->hasChild(nodeName), true);
        currentNode = currentNode->getChild(nodeName);
    }
}

void CodeCoverageTest::testCreateTreeFromStringList()
{
    QString headerFileName("Dir/Project/src/filename.h");
    QString sourceFileName("Dir/Project/src/filename.cpp");
    QStringList fileNames;
    fileNames << headerFileName << sourceFileName;

    TreeCreator treeCreator(fileNames);
    treeCreator.execute();

    Node *rootNode = treeCreator.getRootNode();

    TREE_RECURSIVE_NODE_COMPARE(rootNode, "Dir/Project/src/filename.h");
    TREE_RECURSIVE_NODE_COMPARE(rootNode, "Dir/Project/src/filename.cpp");
}

#include "nodes/FileNode.h"
void CodeCoverageTest::testFileIsLeaf()
{
    QString fileName("Project/filename.h");
    TreeCreator tC(fileName);
    tC.execute();

    Node *rootNode = tC.getRootNode();
    FileNode *fileNode = dynamic_cast<FileNode *>(rootNode->getChild("Project")->getChild("filename.h"));

    QCOMPARE((bool)fileNode, true);
}

#include "tree/ProjectTreeCreator.h"
void CodeCoverageTest::testCreateProjectTree()
{
    QString headerFileName("Project/src/filename.h");
    QString sourceFileName("Project/src/filename.cpp");
    QStringList fileNames;
    fileNames << headerFileName << sourceFileName;
    ProjectTreeCreator pTC(fileNames);
    pTC.execute();

    Node *rootNode = pTC.getRootNode();
    QCOMPARE(rootNode->getName(), QString(""));
    TREE_RECURSIVE_NODE_COMPARE(rootNode, "Project/Headers/src/filename.h");
    TREE_RECURSIVE_NODE_COMPARE(rootNode, "Project/Sources/src/filename.cpp");
}

void CodeCoverageTest::testGetHeaderLeafNodeFromFullName()
{
    QString fileName("Project/src/filename.h");
    QStringList fileNames(fileName);
    ProjectTreeCreator pTC(fileNames);
    pTC.execute();

    Node *leafNode = pTC.getLeafNodeFromFullName("Project/src/filename.h");
    QCOMPARE((bool)leafNode, true);
    QCOMPARE(leafNode->getName(), QString("filename.h"));
    QCOMPARE(leafNode->getFullName(), QString("/Project/Headers/src/filename.h"));
}

void CodeCoverageTest::testGetSourceLeafNodeFromFullName()
{
    QString fileName("Project/src/filename.cpp");
    QStringList fileNames(fileName);
    ProjectTreeCreator pTC(fileNames);
    pTC.execute();

    Node *leafNode = pTC.getLeafNodeFromFullName("Project/src/filename.cpp");
    QCOMPARE((bool)leafNode, true);
    QCOMPARE(leafNode->getName(), QString("filename.cpp"));
    QCOMPARE(leafNode->getFullName(), QString("/Project/Sources/src/filename.cpp"));
}

/*! For now it assumed that coverage process have been finished.
 *  It's time to output file's parsing.
 *  After parsing file named 'coverage.info' there will be input struct for filling project tree.
 */
#include "CoverageInformationParser.h"
void CodeCoverageTest::testCoverageInformationParser()
{
    QStringList fileNamesToParse;
    fileNamesToParse << "/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp";
    QString input("SF:/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp\n"
                  "DA:1,0\n"
                  "DA:2,1\n"
                  "DA:4,0\n"
                  "DA:5,2\n"
                  "DA:10,1\n"
                  "end_of_record\n");

    CoverageInformationParser coverageInformationParser(fileNamesToParse, input);
    coverageInformationParser.execute();

    FileCoverageDataList fileCoverageDataList = coverageInformationParser.getFileCoverageDataList();
    QCOMPARE(fileCoverageDataList.size(), 1);
    FileCoverageData fileCoverageData = fileCoverageDataList.takeFirst();
    QCOMPARE(fileCoverageData.fileName, QString("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp"));
    QCOMPARE(fileCoverageData.lineHitList.size(), 5);
    LineHitList lineHitList = fileCoverageData.lineHitList;
    QCOMPARE(lineHitList.at(0), LineHit(1, 0));
    QCOMPARE(lineHitList.at(1), LineHit(2, 1));
    QCOMPARE(lineHitList.at(2), LineHit(4, 0));
    QCOMPARE(lineHitList.at(3), LineHit(5, 2));
    QCOMPARE(lineHitList.at(4), LineHit(10, 1));
}

void CodeCoverageTest::testCoverateInformationParserNonExistingFileName()
{
    QStringList fileNamesToParse;
    fileNamesToParse << "/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/NonExistingFile.cpp";
    QString input("SF:/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp\n"
                  "DA:1,0\n"
                  "end_of_record\n");

    CoverageInformationParser coverageInformationParser(fileNamesToParse, input);
    coverageInformationParser.execute();

    FileCoverageDataList fileCoverageDataList = coverageInformationParser.getFileCoverageDataList();
    QCOMPARE(fileCoverageDataList.size(), 0);
}

//! For input file coverage data we have to create (or recreate) project tree.
#include "tree/ProjectTreeManager.h"
void CodeCoverageTest::testProjectTreeCreator()
{
    FileCoverageDataList fileCoverageDataList;
    FileCoverageData fileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp");
    fileCoverageData.lineHitList.append(LineHit(0, 1));
    fileCoverageDataList.append(fileCoverageData);
    QString projectName("/home/evgeny/Dropbox/QtSandbox/TestCoverage");

    ProjectTreeManager manager;
    manager.addProject(projectName, fileCoverageDataList);

    Node *rootNode = manager.getRootNode();
    TREE_RECURSIVE_NODE_COMPARE(rootNode, "TestCoverage/Sources/src/app/someclass.cpp");
    FileNode *fileNode = static_cast<FileNode *>(rootNode->getChild("TestCoverage")->getChild("Sources")->getChild("src")->getChild("app")->getChild("someclass.cpp"));
    QCOMPARE(fileNode->getLineHitList().size(), 1);
    QCOMPARE(fileNode->getLineHitList().at(0), LineHit(0, 1));
}

void CodeCoverageTest::testProjectTreeCreatorMoreThanOneProject()
{
    FileCoverageDataList firstFileCoverageDataList;
    FileCoverageData firstFileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp");
    firstFileCoverageData.lineHitList.append(LineHit(0, 1));
    firstFileCoverageDataList.append(firstFileCoverageData);
    QString firstProjectName("/home/evgeny/Dropbox/QtSandbox/TestCoverage");

    FileCoverageDataList secondFileCoverageDataList;
    FileCoverageData secondFileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage#2/src/app/someclass.cpp");
    secondFileCoverageData.lineHitList.append(LineHit(2, 2));
    secondFileCoverageDataList.append(secondFileCoverageData);
    QString secondProjectName("/home/evgeny/Dropbox/QtSandbox/TestCoverage#2");

    ProjectTreeManager manager;
    manager.addProject(firstProjectName, firstFileCoverageDataList);
    manager.addProject(secondProjectName, secondFileCoverageDataList);

    Node *rootNode = manager.getRootNode();
    QCOMPARE(rootNode->getChildren().size(), 2);
    TREE_RECURSIVE_NODE_COMPARE(rootNode, "TestCoverage/Sources/src/app/someclass.cpp");
    FileNode *firstProjectFileNode = static_cast<FileNode *>(rootNode->getChild("TestCoverage")->getChild("Sources")->getChild("src")->getChild("app")->getChild("someclass.cpp"));
    QCOMPARE(firstProjectFileNode->getLineHitList().size(), 1);
    QCOMPARE(firstProjectFileNode->getLineHitList().at(0), LineHit(0, 1));

    TREE_RECURSIVE_NODE_COMPARE(rootNode, "TestCoverage#2/Sources/src/app/someclass.cpp");
    FileNode *secondProjectFileNode = static_cast<FileNode *>(rootNode->getChild("TestCoverage#2")->getChild("Sources")->getChild("src")->getChild("app")->getChild("someclass.cpp"));
    QCOMPARE(secondProjectFileNode->getLineHitList().size(), 1);
    QCOMPARE(secondProjectFileNode->getLineHitList().at(0), LineHit(2, 2));
}

void CodeCoverageTest::testProjectTreeCreatorDublicateProject()
{
    FileCoverageDataList fileCoverageDataList;
    FileCoverageData fileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp");
    fileCoverageData.lineHitList.append(LineHit(0, 1));
    fileCoverageDataList.append(fileCoverageData);
    QString projectName("/home/evgeny/Dropbox/QtSandbox/TestCoverage");

    ProjectTreeManager manager;
    manager.addProject(projectName, fileCoverageDataList);
    manager.addProject(projectName, fileCoverageDataList);

    Node *rootNode = manager.getRootNode();
    QCOMPARE(rootNode->getChildren().size(), 1);
}

void CodeCoverageTest::testProjectTreeCreatorSameProjectWillReplaceOldOne()
{
    FileCoverageDataList oldFileCoverageDataList;
    FileCoverageData oldFileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp");
    oldFileCoverageData.lineHitList.append(LineHit(0, 1));
    oldFileCoverageDataList.append(oldFileCoverageData);

    FileCoverageDataList newFileCoverageDataList;
    FileCoverageData newFileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp");
    newFileCoverageData.lineHitList.append(LineHit(0, 2));
    newFileCoverageData.lineHitList.append(LineHit(1, 3));
    newFileCoverageDataList.append(newFileCoverageData);

    QString projectName("/home/evgeny/Dropbox/QtSandbox/TestCoverage");

    ProjectTreeManager manager;
    manager.addProject(projectName, oldFileCoverageDataList);
    manager.addProject(projectName, newFileCoverageDataList);

    Node *rootNode = manager.getRootNode();
    QCOMPARE(rootNode->getChildren().size(), 1);
    FileNode *firstProjectFileNode = static_cast<FileNode *>(rootNode->getChild("TestCoverage")->getChild("Sources")->getChild("src")->getChild("app")->getChild("someclass.cpp"));
    QCOMPARE(firstProjectFileNode->getLineHitList().size(), 2);
    QCOMPARE(firstProjectFileNode->getLineHitList().at(0), LineHit(0, 2));
    QCOMPARE(firstProjectFileNode->getLineHitList().at(1), LineHit(1, 3));
}

void CodeCoverageTest::testProjectTreeCreatorSameProjectWithAddedFiles()
{
    FileCoverageDataList oldFileCoverageDataList;
    FileCoverageData oldFileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp");
    oldFileCoverageData.lineHitList.append(LineHit(0, 1));
    oldFileCoverageDataList.append(oldFileCoverageData);

    FileCoverageDataList newFileCoverageDataList;
    FileCoverageData firstNewFileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.cpp");
    firstNewFileCoverageData.lineHitList.append(LineHit(0, 2));
    FileCoverageData secondNewFileCoverageData("/home/evgeny/Dropbox/QtSandbox/TestCoverage/src/app/someclass.h");
    secondNewFileCoverageData.lineHitList.append(LineHit(0, 3));
    newFileCoverageDataList.append(firstNewFileCoverageData);
    newFileCoverageDataList.append(secondNewFileCoverageData);

    QString projectName("/home/evgeny/Dropbox/QtSandbox/TestCoverage");

    ProjectTreeManager manager;
    manager.addProject(projectName, oldFileCoverageDataList);
    manager.addProject(projectName, newFileCoverageDataList);

    Node *rootNode = manager.getRootNode();
    QCOMPARE(rootNode->getChildren().size(), 1);

    FileNode *projectFirstFileNode = static_cast<FileNode *>(rootNode->getChild("TestCoverage")->getChild("Sources")->getChild("src")->getChild("app")->getChild("someclass.cpp"));
    QCOMPARE(projectFirstFileNode->getLineHitList().size(), 1);
    QCOMPARE(projectFirstFileNode->getLineHitList().at(0), LineHit(0, 2));

    FileNode *projectSecondFileNode = static_cast<FileNode *>(rootNode->getChild("TestCoverage")->getChild("Headers")->getChild("src")->getChild("app")->getChild("someclass.h"));
    QCOMPARE(projectSecondFileNode->getLineHitList().size(), 1);
    QCOMPARE(projectSecondFileNode->getLineHitList().at(0), LineHit(0, 3));
}

void INITIALIZE_TREE(ProjectTreeManager *projectTreeManager) {
    /*! -
        --P1
        ---Headers
        ----D1
        -----f1.h
        -----f2.h
        -----D2
        ------f1.h
        ------f2.h
        ------f3.h
        ----f1.h
        ----f2.h
        ---Sources
        ----D1
        -----f1.cpp
        -----D2
        ------f1.cpp
        ------f2.cpp
        ----f1.cpp
        ----f2.cpp
     */
    QString projectName("/home/evgeny/P1");
    FileCoverageDataList fileCoverageDataList;

    QStringList fileNames;
    fileNames << "/home/evgeny/P1/D1/f1.h";
    fileNames << "/home/evgeny/P1/D1/f1.cpp";
    fileNames << "/home/evgeny/P1/D1/f2.h";
    fileNames << "/home/evgeny/P1/D2/f1.h";
    fileNames << "/home/evgeny/P1/D2/f1.cpp";
    fileNames << "/home/evgeny/P1/D2/f2.h";
    fileNames << "/home/evgeny/P1/D2/f2.cpp";
    fileNames << "/home/evgeny/P1/D2/f3.h";
    fileNames << "/home/evgeny/P1/f1.h";
    fileNames << "/home/evgeny/P1/f1.cpp";
    fileNames << "/home/evgeny/P1/f2.h";
    fileNames << "/home/evgeny/P1/f2.cpp";

    foreach (const QString &fileName, fileNames)
        fileCoverageDataList.append(FileCoverageData(fileName));

    projectTreeManager->addProject(projectName, fileCoverageDataList);
}

#include "CodeCoverageModel.h"
void CodeCoverageTest::testCodeCoverageModelRowCount()
{
    ProjectTreeManager projectTreeManager;
    INITIALIZE_TREE(&projectTreeManager);
    CodeCoverageModel model(&projectTreeManager);

    QCOMPARE(model.rowCount(QModelIndex()), 1);
    QModelIndex projectIndex = model.index(0, 0, QModelIndex());
    QCOMPARE(model.rowCount(projectIndex), 2);
    QModelIndex headersIndex = model.index(0, 0, projectIndex);
    QCOMPARE(model.rowCount(headersIndex), 4);
    QModelIndex sourcesIndex = model.index(1, 0, projectIndex);
    QCOMPARE(model.rowCount(sourcesIndex), 4);
    QModelIndex D1HIndex = model.index(0, 0, headersIndex);
    QCOMPARE(model.rowCount(D1HIndex), 2);
    QModelIndex D2HIndex = model.index(1, 0, headersIndex);
    QCOMPARE(model.rowCount(D2HIndex), 3);
    QModelIndex D1SIndex = model.index(0, 0, sourcesIndex);
    QCOMPARE(model.rowCount(D1SIndex), 1);
    QModelIndex D2SIndex = model.index(1, 0, sourcesIndex);
    QCOMPARE(model.rowCount(D2SIndex), 2);
}

void CodeCoverageTest::testCodeCoverageModelColumnCount()
{
    ProjectTreeManager projectTreeManager;
    INITIALIZE_TREE(&projectTreeManager);
    CodeCoverageModel model(&projectTreeManager);

    QCOMPARE(model.columnCount(QModelIndex()), 2);
}

QTEST_MAIN(CodeCoverageTest)

#include "tst_CodeCoverageTest.moc"

