#include <calculator.h>
#include <ui_calculator.h>


Calculator::Calculator( QWidget* parent )
     : QWidget{ parent }
     , ui_{ std::make_unique< Ui::Calculator >() }
{
     ui_->setupUi( this );
}


Calculator::~Calculator()
{}
