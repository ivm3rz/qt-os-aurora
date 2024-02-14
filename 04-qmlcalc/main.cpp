#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include <calc.h>


int main( int argc, char* argv[] )
{
     qmlRegisterType< MathEval >( "qmlcalc", 0, 1, "MathEval" );
     QGuiApplication app{ argc, argv };
     QQmlApplicationEngine engine{ ":/calc.qml" };
     return app.exec();
}
