#pragma once

#include <QString>
#include <QList>

struct LineHit {
    LineHit() : pos(0), hit(0) {}
    LineHit(int pos, int hit) : pos(pos), hit(hit) {}

    int pos;
    int hit;

    inline bool operator ==(const LineHit &other) const {
        return pos == other.pos && hit == other.hit;
    }
};

typedef QList<LineHit> LineHitList;

struct FileCoverageData
{
    FileCoverageData() {}
    FileCoverageData(const QString &fileName) : fileName(fileName) {}
    FileCoverageData(const QString &fileName, const LineHitList &lineHitList) : fileName(fileName), lineHitList(lineHitList) {}

    bool isValid() const {
        return !fileName.isEmpty();
    }

    QString fileName;
    LineHitList lineHitList;
};

typedef QList<FileCoverageData> FileCoverageDataList;
