#include <QtCore/QDate>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>


enum CsvColumn
{
     Year,
     Month,
     Day,
     FlagTsunami,
     FlagEarthquake,
     VolcanoName,
};


auto date( const QStringList& row )
{
     const auto year = row.at( Year ).toInt();
     const auto month = row.at( Month ).toInt();
     const auto day = row.at( Day ).toInt();

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
     QStringList headerLabels{ "Дата/год", "Цунами", "Землетрясение", "Название вулкана" };
     widget.setColumnCount( headerLabels.size() );
     widget.setShowGrid( true );
     widget.setSelectionMode( QAbstractItemView::SingleSelection );
     widget.setSelectionBehavior( QAbstractItemView::SelectRows );
     widget.setHorizontalHeaderLabels( headerLabels );
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
               if( const auto tsunamiItem = new QTableWidgetItem() )
               {
                    tsunamiItem->data( Qt::CheckStateRole );
                    tsunamiItem->setCheckState( values.at( FlagTsunami ).contains( "Tsunami" ) ? Qt::Checked : Qt::Unchecked );
                    widget.setItem( index, 1, tsunamiItem );
               }
               if( const auto earthquakeItem = new QTableWidgetItem() )
               {
                    earthquakeItem->data( Qt::CheckStateRole );
                    earthquakeItem->setCheckState( values.at( FlagEarthquake ).contains( "Earthquake" ) ? Qt::Checked : Qt::Unchecked );
                    widget.setItem( index, 2, earthquakeItem );
               }
               widget.setItem( index, 3, new QTableWidgetItem( values.at( VolcanoName ) ) );
          }
     }
     widget.resizeColumnsToContents();
     widget.setWindowTitle( QObject::tr( "Данные о наиболее значимых вулканических извержениях" ) );
     widget.show();

     return app.exec();
}
