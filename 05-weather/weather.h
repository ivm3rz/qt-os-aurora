#pragma once

#include <QtWidgets/QWidget>


QT_BEGIN_NAMESPACE

class QLabel;
class QNetworkAccessManager;

QT_END_NAMESPACE


/// Виджет для отображения погодной информации.
class Weather : public QWidget
{
     Q_OBJECT
public:
     explicit Weather( QWidget* parent = nullptr );

public Q_SLOTS:
     void fetchGeoPosition();
     void fetchWeather( double lat, double lon );
     void fetchIcon( const QString& icon );

private:
     QNetworkAccessManager* network_;
     QLabel* latitude_;
     QLabel* longitude_;
     QLabel* location_;
     QLabel* icon_;
     QLabel* description_;
};
