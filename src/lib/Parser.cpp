#include "Parser.h"

#include <QDebug>

static const int INDEX_NOT_FOUND = -1;

Parser::Parser(const QStringList &fileNames, const QString &content) :
    fileNames(fileNames),
    content(content)
{
}

void Parser::execute()
{
    foreach (const QString fileName, fileNames) {
        const QString &fileCoverageDataContent = getFileCoverageDataContentByName(fileName);
        const FileCoverageData &fileCoverageData = parseFileCoverageDataContent(fileName, fileCoverageDataContent);
        if (fileCoverageData.isValid())
            fileCoverageDataList.append(fileCoverageData);
    }
}

FileCoverageDataList Parser::getFileCoverageDataList() const
{
    return fileCoverageDataList;
}

QString Parser::getFileCoverageDataContentByName(const QString &fileName) const
{
    int beginIndex = content.indexOf(QString("SF:%1").arg(fileName));
    int endIndex = content.indexOf(QString("end_of_record"), beginIndex);

    if (beginIndex != INDEX_NOT_FOUND && endIndex != INDEX_NOT_FOUND)
        return content.mid(beginIndex, endIndex - beginIndex);

    return QString();
}

FileCoverageData Parser::parseFileCoverageDataContent(const QString &fileName, const QString &fileCoverageDataContent) const
{
    if (fileCoverageDataContent.isEmpty())
        return FileCoverageData();

    FileCoverageData fileCoverageData(fileName);
    parseLineHit(&fileCoverageData.lineHitList, fileCoverageDataContent.split('\n'));

    return fileCoverageData;
}

void Parser::parseLineHit(LineHitList *lineHitList, const QStringList &fileCoverageDataStringList) const
{
    const QRegExp rx("^DA:(\\d+),(\\d+)");
    foreach (const QString &fileCoverageDataString, fileCoverageDataStringList) {
        int pos = rx.indexIn(fileCoverageDataString);
        if (pos > -1) {
            LineHit lineHit;
            lineHit.pos = rx.cap(1).toInt();
            lineHit.hit = rx.cap(2).toInt();
            lineHitList->append(lineHit);
        }
    }
}
