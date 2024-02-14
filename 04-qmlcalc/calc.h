#pragma once

#include <QtCore/QObject>

class MathEval : public QObject
{
     Q_OBJECT
public:
     explicit MathEval( QObject* parent = nullptr );

     Q_INVOKABLE double evaluate( const QString& expression );
};
