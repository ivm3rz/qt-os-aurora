#pragma once

#include <QtCore/QObject>

class MathEval : public QObject
{
     Q_OBJECT
     Q_PROPERTY( QString error READ error NOTIFY failed );
public:
     explicit MathEval( QObject* parent = nullptr );

     const QString& error() const noexcept
     {
          return error_;
     }

     Q_INVOKABLE double evaluate( const QString& expression );

Q_SIGNALS:
     void failed();

private:
     QString error_;
};
