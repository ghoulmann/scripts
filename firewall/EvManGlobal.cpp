#include "EvManGlobal.h"

#include <QDebug>
#include <QStringList>

#ifdef Q_OS_WIN
#include <QMessageBox>
#endif

namespace Core {

/*! \fn void Message(const QString &Str)
  Выводит сообщение \arg Str
  */
void Message(const QString &Str)
   {
#ifdef Q_OS_WIN
      QMessageBox::warning(nullptr, "Warning", Str);
#else
      qDebug() << Str;
#endif
   }
}

#include <iostream>
#ifdef Q_OS_UNIX
   #include <execinfo.h>
   #include <QRegExp>
   #include <cxxabi.h>
#endif  // Q_OS_UNIX

#ifdef Q_OS_UNIX
QString Core::Demangle(const QString &RawStr)
   {
#ifdef Q_OS_FREEBSD
      const QRegExp NameRE("<.*\\+");
      const QRegExp OffsetRE("\\+.*>");
      const QRegExp FileNameRE("[^ ]*$");

      if(NameRE.indexIn(RawStr) < 0 || OffsetRE.indexIn(RawStr) < 0 || FileNameRE.indexIn(RawStr) < 0)
         {
            qDebug() << "demangle(const QString &RawStr: Can not parse string: " << RawStr;
            return QString();
         }
      const QString &SymbolName = NameRE.cap().mid(1, NameRE.cap().size() - 2);
      const QString &Offset = OffsetRE.cap().mid(1, OffsetRE.cap().size() - 2);
      const QString &FileName = FileNameRE.cap();
#elif defined(Q_OS_LINUX)
// "/home/tomorrowdawn/QtProjects/lib/libCoreLibrary.so.1(_ZN4Core9Interanal14PrintBacktraceEv+0x2d) [0xa29e16]"
      //qDebug() << RawStr;
      QRegExp FileNameRE("\\([^)]*\\) \\[\\w*\\]$");
      const int EndOfFileName = FileNameRE.indexIn(RawStr);
      if(EndOfFileName == -1)
         {
            qDebug() << "demangle(const QString &RawStr: Can not parse string: " << RawStr;
            return QString();
         }

      const QString &FileName = RawStr.left(EndOfFileName); // /home/tomorrowdawn/QtProjects/lib/libCoreLibrary.so.1
      if(FileName.isEmpty())
         {
            qDebug() << "demangle(const QString &RawStr: FileName is empty in" << RawStr;
            return QString();
         }
      const QString &AllOther = RawStr.right(RawStr.size() - EndOfFileName); // (_ZN4Core9Interanal5PrintEv+0x2d) [0xa29e16]

      QRegExp SymbolNameRE("\\[[^\\]]*\\]$");
      const int SpacePos = SymbolNameRE.indexIn(AllOther);
      if(SpacePos == -1)
         {
            qDebug() << "demangle(const QString &RawStr: Can not parse string: " << AllOther;
            return QString();
         }
      const QString &SymbolNameAndOffset = AllOther.mid(1, SpacePos - 3); // _ZN4Core9Interanal14PrintBacktraceEv+0x2d
      const QString &Unknown = AllOther.right(AllOther.size() - SpacePos); // [0xa29e16]
      Q_UNUSED(Unknown);

      QString SymbolName;
      QString Offset;
      const QStringList &SymbolNameAndOffsetList = SymbolNameAndOffset.split("+0x");
      if(SymbolNameAndOffsetList.size() != 2)
         {
            // /mnt/freedata/home/Void/devel/EventManager/bin/ServerEventManager() [0x4077db]
            return QString();
         }
      else
         {
            SymbolName = SymbolNameAndOffsetList[0];
            Offset = "0x" + SymbolNameAndOffsetList[1];
            if(Offset.isEmpty())
               {
                  qDebug() << "demangle(const QString &RawStr: Offset is empty in" << RawStr;
                  return QString();
               }
         }


#endif
      int Status;
      char *Demangled = abi::__cxa_demangle(SymbolName.toLatin1(), nullptr, nullptr, &Status);
      if(Status != 0)
         return QString();
      return QString(Demangled) + " + Offset=" + Offset + ", at file " + FileName;
   }
#endif //Q_OS_UNIX

QString Core::GetBacktrace()
   {
      QString Result;
      QTextStream Stream(&Result);

      Stream << "========================== Backtrace ==========================\n";

#ifdef Q_OS_UNIX
      const int MAX_BACKTRACE_SIZE = 100;
      void *Array[MAX_BACKTRACE_SIZE];
      size_t Size;
      char **Strings;

      Size = backtrace(Array, MAX_BACKTRACE_SIZE);
      if(Size == 0)
         Stream << "Can not obtain stack trace.";
      else
         {
            Strings = backtrace_symbols(Array, Size);
            Stream << "Obtained " << Size << " stack frames:\n";
            for(size_t i = 0; i < Size; i++)
               {
                  const QString &Demangled = Demangle(Strings[i]);
                  const QString &StrNumber = QString::number(Size - i) + ")";
                  Stream << qSetFieldWidth(5) << left << StrNumber << qSetFieldWidth(0);
                  if(Demangled.isEmpty())
                     Stream << Strings[i];
                  else
                     Stream << Demangled;
                  Stream << "\n";
               }
            free(Strings);
         }
#elif defined(Q_OS_WIN32) || defined(Q_OS_WIN64) // Q_OS_UNIX
      Stream << "Backtrace not supported on Windows yet...";
#endif

      Stream << endl;
      return Result;
   }

void Core::PrintBacktrace()
   {
      qDebug() << GetBacktrace();
   }

namespace Core {
void on_AssertionFailed()
   {
      PrintBacktrace();
      abort();
   }

}

