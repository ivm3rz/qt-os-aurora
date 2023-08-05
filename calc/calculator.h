#pragma once

#include <memory>

#include <QtWidgets/QWidget>

class QAbstractButton;

namespace Ui { class Calculator; }


class Calculator : public QWidget
{
     Q_OBJECT
public:
     explicit Calculator( QWidget *parent = nullptr );
     ~Calculator();

private slots:
     void onDigitClicked();
     void onEqualClicked();
     void onEraseClicked();
     void onBinaryOperatorClicked();
     void onDelimiterClicked();

private:
     QString binaryOperator( const QAbstractButton& ) const;

private:
     std::unique_ptr< Ui::Calculator > ui_;
};
