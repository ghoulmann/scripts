#ifndef FIREWALL_GENERIPARSER_H
#define FIREWALL_GENERIPARSER_H

#include <QStringList>
#include <QTextStream>
#include <QVector>

typedef QStringList TStrFields;
typedef QVector<TStrFields> TStrColumns;
typedef QVector<TStrColumns> TStrRows;
TStrRows Parse(QTextStream &TextStreamt, const int NumberOfColumns);

#endif // FIREWALL_GENERIPARSER_H
