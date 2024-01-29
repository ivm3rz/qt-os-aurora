#include <QtCore/QDate>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>


auto date( const QStringList& row )
{
     const auto year = row.at( 0 ).toInt();
     const auto month = row.at( 1 ).toInt();
     const auto day = row.at( 2 ).toInt();

     return month and day
          ? QDate{ year, month, day }.toString( Qt::ISODate )
          : row.at( 0 )
          ;
}


int main( int argc, char *argv[] )
{
     QApplication app{ argc, argv };

     QFile file{ ":/significant-volcanic-eruption-database.csv" };

     QTableWidget widget;
     widget.setColumnCount( 1 );
     widget.setShowGrid( true );
     widget.setSelectionMode( QAbstractItemView::SingleSelection );
     widget.setSelectionBehavior( QAbstractItemView::SelectRows );
     widget.setHorizontalHeaderLabels( QStringList() << "Дата/год" << "Флаг цунами" );
     widget.horizontalHeader()->setStretchLastSection( true );

     if( file.open( QFile::ReadOnly | QFile::Text ) )
     {
          QTextStream in{ &file };
          while( !in.atEnd() )
          {
               const auto each = in.readLine();
               const auto values = each.split( ";" );
               const auto index = widget.rowCount();
               widget.insertRow( index );

               if( const auto dateItem = new QTableWidgetItem() )
               {
                    dateItem->setData( Qt::DisplayRole, date( values ) );
                    widget.setItem( index, 0, dateItem );
               }
          }
     }

     widget.resizeColumnsToContents();
     widget.setWindowTitle( QObject::tr( "Данные о наиболее значимых вулканических извержениях" ) );
     widget.show();

     return app.exec();
}
