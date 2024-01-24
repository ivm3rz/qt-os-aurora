#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

int main( int argc, char *argv[] )
{
     QCoreApplication app{ argc, argv };

     QFile file{ ":/significant-volcanic-eruption-database.csv" };
     if( file.open( QFile::ReadOnly | QFile::Text ) )
     {
          QTextStream in{ &file };
          while( !in.atEnd() )
          {
               // for( const auto& each: .split( "," ) )
               {
                    qDebug() << in.readLine();
               }
          }
     }
     return EXIT_SUCCESS;
}
