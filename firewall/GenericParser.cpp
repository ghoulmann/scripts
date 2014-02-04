#include "GenericParser.h"
#include "EvManGlobal.h"

#include <QRegularExpression>

const QString BEGIN = "BEGIN";
const QString END = "END";
const QString COLUMN_SEPARATOR = ";";
const QString FIELD_SEPARATOR = ",";

void RemoveLeadingSpacesIfAny(QString &Line)
   {
      Line.remove(QRegExp("^ *"));
   }

void SkipAllUntillBegin(QTextStream &TextStream)
   {
      for(; !TextStream.atEnd(); )
         {
            QString Line = TextStream.readLine();

            RemoveLeadingSpacesIfAny(Line);

            if(Line.startsWith('#'))
               continue;

            if(Line.startsWith(BEGIN))
               break;
         }
   }

TStrRows Parse(QTextStream &TextStream, const int NumberOfColumns)
   {
      SkipAllUntillBegin(TextStream);

      TStrRows Result;
      for(; !TextStream.atEnd(); )
         {
            QString Line = TextStream.readLine();
            RemoveLeadingSpacesIfAny(Line);
            if(Line.startsWith('#'))
               continue;
            if(Line.isEmpty())
               continue;
            if(Line.startsWith(END))
               break;

            const QStringList &Columns = Line.split(COLUMN_SEPARATOR);
            ASSERT_OP(Columns.size(), ==, NumberOfColumns);
            TStrColumns StrColumns;
            for(const QString &Column: Columns)
               {
                  TStrFields Fields = Column.split(FIELD_SEPARATOR);
                  for(QString &Field: Fields)
                     {
                        Field.remove(QRegularExpression("^[ \t]*"));
                        Field.remove(QRegularExpression("[ \t]*$"));
                     }
                  StrColumns << Fields;
               }
            ASSERT_OP(StrColumns.size(), ==, NumberOfColumns);
            Result << StrColumns;
         }
      return Result;
   }
