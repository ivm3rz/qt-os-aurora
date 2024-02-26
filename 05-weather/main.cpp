#include <QtCore/QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


int main( int argc, char *argv[] )
{
     QCoreApplication app{ argc,argv };
     QNetworkAccessManager networkManager;
     const auto reply = networkManager.get( QNetworkRequest{ QUrl{ "http://ifconfig.co/json" } } );

     QObject::connect(
          reply
          , &QNetworkReply::readyRead
          , [ reply ]
          {
               qDebug().noquote() << reply->readAll();
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

     return app.exec();
}
