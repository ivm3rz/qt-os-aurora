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

private:
     std::unique_ptr< Ui::Calculator > ui_;
};
