#pragma once

#include <memory>

#include <QtWidgets/QWidget>

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

private:
     std::unique_ptr< Ui::Calculator > ui_;
};
