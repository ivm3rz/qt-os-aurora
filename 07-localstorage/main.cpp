#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#ifdef USE_SAILFISH_APP
#include <sailfishapp/sailfishapp.h>
#else
#include <auroraapp/auroraapp.h>
#endif

int main( int argc, char *argv[] )
{
#ifdef USE_SAILFISH_APP
     // FIXME: unable to use broken `Aurora::Application::main` (as well as `Auorora::Application::pathToMainQml`)
     return SailfishApp::main( argc, argv );
#else
     return Aurora::Application::main( argc, argv );
#endif
}
