#include <memory>

#include <QFile>

#include "GenericParser.h"
#include "EvManGlobal.h"

int main(int argc, char **argv)
   {
      std::unique_ptr<QTextStream> Stream;
      QFile ConfigFile;
      if(argc >= 2)
         {
            ConfigFile.setFileName(argv[1]);
            const bool Ok = ConfigFile.open(QFile::ReadOnly);
            ASSERT(Ok);
            Stream = std::unique_ptr<QTextStream>(new QTextStream(&ConfigFile));
         }
      else
         {
            Stream = std::unique_ptr<QTextStream>(new QTextStream(stdin, QIODevice::ReadOnly));
         }

      TStrRows ProtocolInfoTable = Parse(*Stream, 3);

      return 0;
   }
