#include "weather.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QUrlQuery>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFormLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


static const auto apiKey = "bd5e378503939ddaee76f12ad7a97608";


Weather::Weather( QWidget* parent )
     : QWidget{ parent }
     , network_{ new QNetworkAccessManager( this ) }
     , latitude_{ new QLabel( this ) }
     , longitude_{ new QLabel( this ) }
     , location_{ new QLabel( this ) }
     , icon_{ new QLabel( this ) }
     , description_{ new QLabel( this ) }
{
     setWindowTitle( tr( "Weather⛅" ) );

     const auto locLayout = new QFormLayout;
     locLayout->addRow( tr( "Latitude:" ), latitude_ );
     locLayout->addRow( tr( "Longitude:" ), longitude_ );
     locLayout->addRow( tr( "Location:" ), location_ );

     const auto weatherLayout = new QHBoxLayout;
     weatherLayout->addWidget( icon_ );
     weatherLayout->addWidget( description_ );
     description_->setStyleSheet( "font: 18pt;" );

     const auto mainLayout = new QVBoxLayout( this );
     mainLayout->addLayout( locLayout );
     mainLayout->addLayout( weatherLayout );
     mainLayout->addItem( new QSpacerItem( 0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding ) );

     fetchGeoPosition();
}


void Weather::fetchGeoPosition()
{
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
     QUrlQuery query;
     query.addQueryItem( "lat", QString::number( latitude ) );
     query.addQueryItem( "lon", QString::number( longitude ) );
     query.addQueryItem( "appid", apiKey );
     query.addQueryItem( "units", "metric" );

     QUrl url{ "https://api.openweathermap.org/data/2.5/weather" };
     url.setQuery( query );

     const auto reply = network_->get( QNetworkRequest{ url } );

     connect(
          reply
          , &QNetworkReply::readyRead
          , [ reply, this ]
          {
               const auto& json = reply->readAll();
               qDebug().noquote() << json;

               const auto document = QJsonDocument::fromJson( json );
               for( const auto& each: document[ "weather" ].toArray() )
               {
                    if( each.isObject() )
                    {
                         const auto& weather = each.toObject();
                         description_->setText( weather[ "description" ].toString() );
                         fetchIcon( weather[ "icon" ].toString() );
                         break;
                    }
               }
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


void Weather::fetchIcon( const QString& icon )
{
     static const QString url = "https://openweathermap.org/img/wn/";

     const auto reply = network_->get( QNetworkRequest{ url + icon + ".png" } );

     connect(
          reply
          , &QNetworkReply::readyRead
          , [ reply, this ]
          {
               QPixmap pixmap;
               if( pixmap.loadFromData( reply->readAll() ) )
               {
                    icon_->setPixmap( pixmap );
               }
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
