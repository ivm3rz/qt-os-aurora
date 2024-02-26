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

     const auto formLayout = new QFormLayout( &widget );
     const auto latitude = new QLabel( &widget );
     const auto longitude = new QLabel( &widget );
     formLayout->addRow( QObject::tr( "Latitude:" ), latitude );
     formLayout->addRow( QObject::tr( "Longitude" ), longitude );
     widget.setLayout( formLayout );

     QNetworkAccessManager networkManager;
     const auto reply = networkManager.get( QNetworkRequest{ QUrl{ "http://ifconfig.co/json" } } );

     QObject::connect(
          reply
          , &QNetworkReply::readyRead
          , [ reply, latitude, longitude ]
          {
               const auto& json = reply->readAll();
               qDebug().noquote() << json;
               const auto& document = QJsonDocument::fromJson( json );
               latitude->setNum( document[ "latitude" ].toDouble() );
               longitude->setNum( document[ "longitude" ].toDouble() );
          }
     );

     QObject::connect(
          reply
          , &QNetworkReply::errorOccurred
          , [ reply ]
          {
               qDebug() << "Error: " + reply->errorString();
          }
     );

     QObject::connect(
          reply
          , &QNetworkReply::finished
          , reply
          , &QNetworkReply::deleteLater
     );
     widget.setWindowTitle( "Weather⛅" );
     widget.show();
     return app.exec();
}
