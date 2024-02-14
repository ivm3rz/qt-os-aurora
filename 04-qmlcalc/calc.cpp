#include <calc.h>

#include <limits>

#include <matheval.hpp>

#include <QtCore/QDebug>


MathEval::MathEval( QObject* parent )
     : QObject{ parent }
{}


double MathEval::evaluate( const QString& expression ) try
{
     error_.clear();
     return matheval::parse( expression.toStdString() );
}
catch( const std::exception& e )
{
     if( error_.isEmpty() )
     {
          error_ = e.what();
          emit failed();
     }
     qDebug() << __FUNCTION__ << error_;
     return std::numeric_limits< double >::quiet_NaN();
}
