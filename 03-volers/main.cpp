#include <QtCore/QDate>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
     Location,
     Country,
     Elevation,
     VolcanoType,
     Status,
     Explosivity,
};


auto date( const QStringList& row )
{
     const auto year = row.at( Year ).toInt();
     const auto month = row.at( Month ).toInt();
     const auto day = row.at( Day ).toInt();

     return month and day
          ? QDate{ year, month, day }.toString( Qt::ISODate )
          : year >= 0
               ? QString::number( year ) + QObject::tr(" г." )
               : QString::number( -year ) + QObject::tr(" г. до н.э." )
          ;
}


QPixmap flag( const QString& country )
{
     static const QMap< QString, QString > countryFlags
     {
          { "Indonesia", ":/flags/id.png" },
          { "Japan",     ":/flags/jp.png" },
          { "Italy",     ":/flags/it.png" },
          { "Chile",     ":/flags/cl.png" },
          { "Spain",     ":/flags/es.png" },
          { "Ecuador",   ":/flags/ec.png" },
          { "Iceland",   ":/flags/is.png" },
     };
     const auto& flag = countryFlags.value( country );
     if( flag.isEmpty() )
     {
          return {};
     }
     return QPixmap{ flag };
}


int main( int argc, char *argv[] )
{
     QApplication app{ argc, argv };

     QFile file{ ":/significant-volcanic-eruption-database.csv" };

     QTableWidget widget;
     QStringList headerLabels{ "Дата/год", "Цунами", "Землетрясение", "Название вулкана", "Местонахождение", "Страна", "Высота, м", "Тип вулкана", "Статус", "Индекс вулканической активности" };
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
               const auto rowIndex = widget.rowCount();
               auto columnIndex = 0;

               widget.insertRow( rowIndex );

               if( const auto item = new QTableWidgetItem() )
               {
                    item->setData( Qt::DisplayRole, date( values ) );
                    widget.setItem( rowIndex, columnIndex++, item );
               }
               if( const auto item = new QTableWidgetItem() )
               {
                    item->data( Qt::CheckStateRole );
                    item->setCheckState( values.at( FlagTsunami ).contains( "Tsunami" ) ? Qt::Checked : Qt::Unchecked );
                    widget.setItem( rowIndex, columnIndex++, item );
               }
               if( const auto item = new QTableWidgetItem() )
               {
                    item->data( Qt::CheckStateRole );
                    item->setCheckState( values.at( FlagEarthquake ).contains( "Earthquake" ) ? Qt::Checked : Qt::Unchecked );
                    widget.setItem( rowIndex, columnIndex++, item );
               }
               widget.setItem( rowIndex, columnIndex++, new QTableWidgetItem( values.at( VolcanoName ) ) );
               widget.setItem( rowIndex, columnIndex++, new QTableWidgetItem( values.at( Location ) ) );
               if( const auto item = new QTableWidgetItem() )
               {
                    const auto country = values.at( Country );
                    item->setData( Qt::DisplayRole, country );
                    item->setData( Qt::DecorationRole, flag( country ) );
                    widget.setItem( rowIndex, columnIndex++, item );
               };
               if( const auto item = new QTableWidgetItem() )
               {
                    item->setData( Qt::DisplayRole, values.at( Elevation ).toInt() );
                    widget.setItem( rowIndex, columnIndex++, item );
               }
               widget.setItem( rowIndex, columnIndex++, new QTableWidgetItem( values.at( VolcanoType ) ) );
               widget.setItem( rowIndex, columnIndex++, new QTableWidgetItem( values.at( Status ) ) );
               widget.setItem( rowIndex, columnIndex, new QTableWidgetItem( values.at( Explosivity ) ) );
          }
     }
     widget.resizeColumnsToContents();
     widget.setWindowTitle( QObject::tr( "Данные о наиболее значимых вулканических извержениях" ) );
     widget.setSizeAdjustPolicy( QAbstractScrollArea::AdjustToContents );
     widget.show();

     app.setWindowIcon( QPixmap{ ":/volcano_icon_24" } );

     return app.exec();
}
