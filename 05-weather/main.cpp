#include "weather.h"

#include <QtWidgets/QApplication>


int main( int argc, char *argv[] )
{
     QApplication app{ argc,argv };
     Weather widget;
     widget.resize( 320, 240 );
     widget.show();
     return app.exec();
}
