#include <calc.h>

#include <limits>

#include <matheval.hpp>

#include <QtCore/QDebug>


MathEval::MathEval( QObject* parent )
     : QObject{ parent }
{}


double MathEval::evaluate( const QString& expression ) try
{
     return matheval::parse( expression.toStdString() );
}
catch( const std::exception& e )
{
     qDebug() << __FUNCTION__ << e.what();
     return std::numeric_limits< double >::quiet_NaN();
}
