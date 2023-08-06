#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

#include <progress_widget.h>

int main( int argc, char *argv[] )
{
     QApplication app{ argc, argv };
     QDialogButtonBox dlg{ QDialogButtonBox::Cancel };
     auto actionButton = dlg.addButton( "Загрузка", QDialogButtonBox::ActionRole );
     auto progress = new ProgressWidget( &dlg, "Загрузка", { "", ".", "..", "..." }, false );

     QObject::connect(
          actionButton
          , &QPushButton::clicked
          , [ progress ]
          {
               progress->setTextAnimationSpeedFraction( 5 );
               progress->startAnimation();
          }
     );

     QObject::connect(
          progress
          , &ProgressWidget::cancelled
          , [ progress ]
          {
               progress->endAnimation();
          }
     );

     dlg.setCenterButtons( true );
     dlg.resize( 200, 200 );
     dlg.show();
     return app.exec();
}
