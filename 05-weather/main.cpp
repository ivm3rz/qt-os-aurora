#include "weather.h"

#include <QtWidgets/QApplication>


int main( int argc, char *argv[] )
{
     QApplication app{ argc,argv };
     Weather weather;
     weather.show();
     return app.exec();
}
