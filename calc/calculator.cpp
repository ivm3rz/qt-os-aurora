#include <calculator.h>

#include <matheval.hpp>

#include <ui_calculator.h>


static const QString exclamation = "❗";


Calculator::Calculator( QWidget* parent )
     : QWidget{ parent }
     , ui_{ std::make_unique< Ui::Calculator >() }
{
     ui_->setupUi( this );

     connect( ui_->zeroButton , SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->oneButton  , SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->twoButton  , SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->threeButton, SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->fourButton , SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->fiveButton , SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->sixButton  , SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->sevenButton, SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->eightButton, SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );
     connect( ui_->nineButton , SIGNAL( clicked() ), this, SLOT( onDigitClicked() ) );

     connect( ui_->addButton      , SIGNAL( clicked() ), this, SLOT( onBinaryOperatorClicked() ) );
     connect( ui_->subtractButton , SIGNAL( clicked() ), this, SLOT( onBinaryOperatorClicked() ) );
     connect( ui_->multiplyButton , SIGNAL( clicked() ), this, SLOT( onBinaryOperatorClicked() ) );
     connect( ui_->divideButton   , SIGNAL( clicked() ), this, SLOT( onBinaryOperatorClicked() ) );

     connect( ui_->eraseButton, SIGNAL( clicked() ), this, SLOT( onEraseClicked() ) );
     connect( ui_->equalButton, SIGNAL( clicked() ), this, SLOT( onEqualClicked() ) );

     connect( ui_->delimiterButton, SIGNAL( clicked() ), this, SLOT( onDelimiterClicked() ) );
}


Calculator::~Calculator()
{}


void Calculator::onDigitClicked()
{
     if( const auto clickedButton = qobject_cast< QAbstractButton* >( sender() ) )
     {
          const auto digitValue = clickedButton->text().toInt();

          auto display = ui_->display->text();

          if( display == "0" || display == exclamation )
          {
               ui_->display->setText( QString::number( digitValue ) );
          }
          else
          {
               ui_->display->setText( ui_->display->text() + QString::number( digitValue ) );
          }
     }
     ui_->display->setToolTip( {} );
}


void Calculator::onEqualClicked() try
{
     if( ui_->display->text() == exclamation )
     {
          return;
     }
     ui_->display->setText( QString::number( matheval::parse( ui_->display->text().toStdString() ) ) );
}
catch( const std::exception& e )
{
     ui_->display->setText( exclamation );
     ui_->display->setToolTip( e.what() );
}


void Calculator::onEraseClicked()
{
     auto text = ui_->display->text();
     text.chop( 1 );
     ui_->display->setText( text.isEmpty() ? "0" : text );
}


void Calculator::onBinaryOperatorClicked()
{
     if( const auto button = qobject_cast< QAbstractButton* >( sender() ) )
     {
          if( ui_->display->text() == exclamation )
          {
               return;
          }
          ui_->display->setText( ui_->display->text() + binaryOperator( *button ) );
     }
}


QString Calculator::binaryOperator( const QAbstractButton& button ) const
{
     if( button.objectName() == "divideButton" )
     {
          return "/";
     }
     if( button.objectName() == "multiplyButton" )
     {
          return "*";
     }
     if( button.objectName() == "subtractButton" )
     {
          return "-";
     }
     return button.text();
}


void Calculator::onDelimiterClicked()
{
     if( const auto button = qobject_cast< QAbstractButton* >( sender() ) )
     {
          static const auto delimiter = ".";

          const auto display = ui_->display->text();

          if( display.endsWith( delimiter ) )
          {
               return;
          }
          ui_->display->setText( ui_->display->text() +  delimiter );
     }
}
