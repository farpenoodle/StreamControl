#ifndef CSV_H
#define CSV_H

#include <QStringList>

namespace CSV
{
    QList<QStringList> parseFromString(const QString &string);
    QList<QStringList> parseFromFile(const QString &filename, const QString &codec = "Shift-JIS");
    bool write(const QList<QStringList> data, const QString &filename, const QString &codec = "Shift-JIS");
}

#endif // CSV_H
