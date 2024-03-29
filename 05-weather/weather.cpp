#include "weather.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QTimer>
#include <QtCore/QUrlQuery>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFormLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


static const auto updateTimeout = 60 * 1000;
static const auto apiKey = "bd5e378503939ddaee76f12ad7a97608";


Weather::Weather( QWidget* parent )
     : QWidget{ parent }
     , network_{ new QNetworkAccessManager( this ) }
     , latitude_{ new QLabel( this ) }
     , longitude_{ new QLabel( this ) }
     , location_{ new QLabel( this ) }
     , icon_{ new QLabel( this ) }
     , description_{ new QLabel( this ) }
     , temperature_{ new QLabel( this ) }
     , feelsLike_{ new QLabel( this ) }
     , humidity_{ new QLabel( this ) }
     , pressure_{ new QLabel( this ) }
     , timestamp_{ new QLabel( this ) }
     , link_{ new QLabel( this ) }
     , updateTimer_{ new QTimer( this ) }
{
     setWindowTitle( tr( "Weather⛅" ) );
     setStyleSheet( "background-color: #7e7f83;" );

     const auto locLayout = new QFormLayout;
     locLayout->addRow( tr( "Latitude:" ), latitude_ );
     locLayout->addRow( tr( "Longitude:" ), longitude_ );
     locLayout->addRow( tr( "Location:" ), location_ );
     locLayout->setFormAlignment( Qt::AlignVCenter );

     const auto weatherLayout = new QFormLayout;
     weatherLayout->addRow( tr( "Temperature:" ), temperature_ );
     weatherLayout->addRow( tr( "Feels Like:" ), feelsLike_ );
     weatherLayout->addRow( tr( "Humidity:" ), humidity_ );
     weatherLayout->addRow( tr( "Pressure:" ), pressure_ );
     weatherLayout->setFormAlignment( Qt::AlignVCenter );

     const auto hboxLayout = new QHBoxLayout;
     hboxLayout->addLayout( locLayout );
     hboxLayout->addWidget( icon_ );
     hboxLayout->addWidget( description_ );
     hboxLayout->addLayout( weatherLayout );
     {
          description_->setStyleSheet( "font: 18pt;" );
     }
     const auto statusLayout = new QHBoxLayout;
     statusLayout->addWidget( timestamp_ );
     statusLayout->addWidget( link_ );
     {
          link_->setText( R"html(<a href="https://openweathermap.org/current">OpenWeatherMap</a>)html" );
          link_->setTextFormat( Qt::RichText );
          link_->setOpenExternalLinks( true );
     }
     const auto mainLayout = new QVBoxLayout( this );
     mainLayout->addLayout( hboxLayout );
     mainLayout->addItem( new QSpacerItem( 0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding ) );
     mainLayout->addLayout( statusLayout );

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

               connect(
                    updateTimer_
                    , &QTimer::timeout
                    , [ latitude, longitude, this ]
                    {
                         qDebug() << QDateTime::currentSecsSinceEpoch();
                         fetchWeather( latitude, longitude );
                    }
               );

               updateTimer_->start( updateTimeout );
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
               const auto& weather = document[ "main" ].toObject();
               temperature_->setText( QString( "%1 °C" ).arg( weather[ "temp" ].toDouble() ) );
               feelsLike_->setText( QString( "%1 °C" ).arg( weather[ "feels_like" ].toDouble() ) );
               humidity_->setText( QString( "%1 %" ).arg( weather[ "humidity" ].toInt() ) );
               pressure_->setText( tr( "%1 hPa" ).arg( weather[ "pressure" ].toInt() ) );
               QDateTime dt;
               dt.setSecsSinceEpoch( document[ "dt" ].toInt() );
               timestamp_->setText( tr( "As of " ) + dt.toString() );
          }
     );

     connect(
          reply
          , &QNetworkReply::errorOccurred
          , [ reply, this ]
          {
               qDebug() << "Error: " + reply->errorString();
               temperature_->setText( "--" );
               feelsLike_->setText( "--" );
               humidity_->setText( "-- " );
               pressure_->setText( "-- " );
               timestamp_->setText( "--" );
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

     const auto reply = network_->get( QNetworkRequest{ url + icon + "@2x.png" } );

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
