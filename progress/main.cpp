#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

#include <progress_widget.h>

int main( int argc, char *argv[] )
{
     QApplication app{ argc, argv };

     QDialogButtonBox dlg;
     auto loadButton = dlg.addButton( "Загрузка", QDialogButtonBox::ActionRole );
     auto connectButton = dlg.addButton( "Подключение", QDialogButtonBox::ActionRole );

     auto loadProgress = new ProgressWidget( &dlg, "Загрузка", { "", ".", "..", "..." }, false );
     auto connectProgress = new ProgressWidget( &dlg, "Подключение", { "", ".", "..", "..." }, false );

     QObject::connect(
          loadButton
          , &QPushButton::clicked
          , [ loadProgress ]
          {
               loadProgress->setMode( ProgressWidget::Mode::Discrete );
               loadProgress->startAnimation();
          }
     );

     QObject::connect(
          connectButton
          , &QPushButton::clicked
          , [ connectProgress ]
          {
               connectProgress->setMode( ProgressWidget::Mode::Solid );
               connectProgress->startAnimation();
          }
     );

     QObject::connect(
          loadProgress
          , &ProgressWidget::cancelled
          , [ loadProgress ]
          {
               loadProgress->endAnimation();
          }
     );

     QObject::connect(
          connectProgress
          , &ProgressWidget::cancelled
          , [ connectProgress ]
          {
               connectProgress->endAnimation();
          }
     );

     dlg.setCenterButtons( true );
     dlg.resize( 200, 200 );
     dlg.show();
     return app.exec();
}
