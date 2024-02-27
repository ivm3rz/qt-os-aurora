#include "weather.h"

#include <QtCore/QJsonDocument>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFormLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


Weather::Weather( QWidget* parent )
     : QWidget{ parent }
     , net_{ new QNetworkAccessManager( this ) }
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

     const auto reply = net_->get( QNetworkRequest{ QUrl{ "http://ifconfig.co/json" } } );

     QObject::connect(
          reply
          , &QNetworkReply::readyRead
          , [ reply, this ]
          {
               const auto& json = reply->readAll();
               qDebug().noquote() << json;
               const auto& document = QJsonDocument::fromJson( json );
               latitude_->setNum( document[ "latitude" ].toDouble() );
               longitude_->setNum( document[ "longitude" ].toDouble() );
               location_->setText( document[ "country" ].toString() + "/" + document[ "city" ].toString() );
          }
     );

     QObject::connect(
          reply
          , &QNetworkReply::errorOccurred
          , [ reply, this ]
          {
               qDebug() << "Error: " + reply->errorString();
               latitude_->setText( "--" );
               longitude_->setText( "--" );
               location_->setText( "-- " );
          }
     );

     QObject::connect(
          reply
          , &QNetworkReply::finished
          , reply
          , &QNetworkReply::deleteLater
     );
}
