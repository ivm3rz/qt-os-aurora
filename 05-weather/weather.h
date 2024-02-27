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

private:
     QNetworkAccessManager* net_;
     QLabel* latitude_;
     QLabel* longitude_;
     QLabel* location_;
};
