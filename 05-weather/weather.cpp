#include "weather.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QUrlQuery>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFormLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


Weather::Weather( QWidget* parent )
     : QWidget{ parent }
     , network_{ new QNetworkAccessManager( this ) }
     , latitude_{ new QLabel( this ) }
     , longitude_{ new QLabel( this ) }
     , location_{ new QLabel( this ) }
{
     setWindowTitle( tr( "Weather⛅" ) );

     const auto formLayout = new QFormLayout;
     formLayout->addRow( tr( "Latitude:" ), latitude_ );
     formLayout->addRow( tr( "Longitude:" ), longitude_ );
     formLayout->addRow( tr( "Location:" ), location_ );

     const auto mainLayout = new QVBoxLayout( this );
     mainLayout->addLayout( formLayout );
     mainLayout->addItem( new QSpacerItem( 0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding ) );

     const auto reply = network_->get( QNetworkRequest{ QUrl{ "http://ifconfig.co/json" } } );

     connect(
          reply
          , &QNetworkReply::readyRead
          , [ reply, this ]
          {
               const auto& json = reply->readAll();
               qDebug().noquote() << json;

               const auto document = QJsonDocument::fromJson( json );
               const auto latitude = document[ "latitude" ].toDouble();
               const auto longitude = document[ "longitude" ].toDouble();
               latitude_->setNum( latitude );
               longitude_->setNum( longitude );
               location_->setText( document[ "country" ].toString() + "/" + document[ "city" ].toString() );

               fetchWeather( latitude, longitude );
          }
     );

     connect(
          reply
          , &QNetworkReply::errorOccurred
          , [ reply, this ]
          {
               qDebug() << "Error: " + reply->errorString();
               latitude_->setText( "--" );
               longitude_->setText( "--" );
               location_->setText( "-- " );
               setToolTip( reply->errorString() );
          }
     );

     connect(
          reply
          , &QNetworkReply::finished
          , reply
          , &QNetworkReply::deleteLater
     );
}


void Weather::fetchWeather( double latitude, double longitude )
{
     static const auto apiKey = "bd5e378503939ddaee76f12ad7a97608";

     QUrlQuery query;
     query.addQueryItem( "lat", QString::number( latitude ) );
     query.addQueryItem( "lon", QString::number( longitude ) );
     query.addQueryItem( "appid", apiKey );

     QUrl url{ "https://api.openweathermap.org/data/2.5/weather" };
     url.setQuery( query );

     const auto reply = network_->get( QNetworkRequest{ url } );

     connect(
          reply
          , &QNetworkReply::readyRead
          , [ reply, this ]
          {
               qDebug().noquote() << reply->readAll();
          }
     );

     connect(
          reply
          , &QNetworkReply::errorOccurred
          , [ reply, this ]
          {
               qDebug() << "Error: " + reply->errorString();
          }
     );

     connect(
          reply
          , &QNetworkReply::finished
          , reply
          , &QNetworkReply::deleteLater
     );
}
