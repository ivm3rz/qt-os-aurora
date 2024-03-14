#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#ifdef USE_SAILFISH_APP
#include <sailfishapp/sailfishapp.h>
#else
#include <libauororaapp/libauroraapp.h>
#endif

int main( int argc, char *argv[] )
{
     // FIXME: unable to use broken `Aurora::Application::main` (as well as `Auorora::Application::pathToMainQml`)
     return SailfishApp::main( argc, argv );
}
