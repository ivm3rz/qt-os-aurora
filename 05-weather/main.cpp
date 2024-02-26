#include <QtCore/QJsonDocument>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


int main( int argc, char *argv[] )
{
     QApplication app{ argc,argv };

     QWidget widget;

     const auto formLayout = new QFormLayout;
     const auto latitude = new QLabel( &widget );
     const auto longitude = new QLabel( &widget );
     const auto location = new QLabel( &widget );
     formLayout->addRow( QObject::tr( "Latitude:" ), latitude );
     formLayout->addRow( QObject::tr( "Longitude:" ), longitude );
     formLayout->addRow( QObject::tr( "Location:" ), location );
     widget.setLayout( formLayout );

     QNetworkAccessManager networkManager;
     const auto reply = networkManager.get( QNetworkRequest{ QUrl{ "http://ifconfig.co/json" } } );

     QObject::connect(
          reply
          , &QNetworkReply::readyRead
          , [ reply, latitude, longitude, location ]
          {
               const auto& json = reply->readAll();
               qDebug().noquote() << json;
               const auto& document = QJsonDocument::fromJson( json );
               latitude->setNum( document[ "latitude" ].toDouble() );
               longitude->setNum( document[ "longitude" ].toDouble() );
               location->setText( document[ "country" ].toString() + "/" + document[ "city" ].toString() );
          }
     );

     QObject::connect(
          reply
          , &QNetworkReply::errorOccurred
          , [ reply, latitude, longitude, location ]
          {
               qDebug() << "Error: " + reply->errorString();
               latitude->setText( "--" );
               longitude->setText( "--" );
               location->setText( "-- " );
          }
     );

     QObject::connect(
          reply
          , &QNetworkReply::finished
          , reply
          , &QNetworkReply::deleteLater
     );
     widget.resize( 320, 240 );
     widget.setWindowTitle( "Weather⛅" );
     widget.show();
     return app.exec();
}
