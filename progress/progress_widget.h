#pragma once

#include <QtCore/QMargins>
#include <QtCore/QPointer>
#include <QtGui/QColor>
#include <QtWidgets/QWidget>

class QElapsedTimer;
class QTimer;

////
/// Виджет, позволяющей закрывать указанный виджет и отображать анимацию,
/// сигнализирующую о выполнении объемной задачи. Можно установить два вида
/// графических индикаторов. Под графическим индикатором можно расположить
/// текст, обычно честно отображающий суть происходящего процесса и
/// подсказывающий пользователю, почему он должен набраться терпения и тратить
/// своё "царское" время. Этот текст тоже можно анимировать (например, написать
/// "Загрузка..." и изменять количество точек в конце предложения).
///
/// @code
/// ProgressWidget::discrete( this, "Загрузка", { "", ".", "..", "..." } );
/// ProgressWidget::solid( this, "Подключение", { ".", "..", "..." } );
/// @endcode
///
class ProgressWidget : public QWidget
{
     Q_OBJECT
     Q_DISABLE_COPY( ProgressWidget )

public:
     enum class Mode
     {
          Discrete                      ///< Ромашка
          , Solid                       ///< Сплошная ромашка
     };

     enum class Color
     {
          Start,         // Начальный цвет градиента
          End,           // Конечный цвет градиента
          Text,          // Цвет текста (default: white)
          Background     // Цвет фона
     };

public:
     explicit ProgressWidget(
          QWidget* parent
          , const QString& text
          , const QStringList& textAnimation
          , bool startAnimation = true
     );

     ~ProgressWidget();

     void setMode( Mode );
     void setRingWidth( int );
     void setRingRadius( int );
     void setTextAnimationSpeedFraction( int );

public:
     static ProgressWidget* discrete(
          QWidget* parent
          , const QString& text
          , const QStringList& textAnimation
          , const QColor& start = QColor( 255, 255, 255, 0 )
          , const QColor& end = QColor( 255, 255, 255, 255 )
     );

     static ProgressWidget* solid(
          QWidget* parent
          , const QString& text
          , const QStringList& textAnimation
          , const QColor& start = QColor( 255, 255, 255, 0 )
          , const QColor& end = QColor( 255, 255, 255, 255 )
     );

public slots:
     void setColor( const QColor& color, Color colorType );

     virtual void startAnimation();
     virtual void endAnimation( bool doSelfDelete = false );

     void setAnimationState( const bool doAnimate );

signals:
     /// Высылается при отмене операции пользователем.
     void userCancelled();
     void animateStateChanged( bool isAimatedNow );

protected:
     bool eventFilter( QObject* o, QEvent* e ) override;
     void paintEvent( QPaintEvent* e ) override;
     void keyPressEvent( QKeyEvent* e ) override;

     void startDelayTimer();

protected slots:
     void timerTimeout();
     void prepareAndShow();

private:
     Mode mode_;                        // Тип индикатора
     QString text_;                     // Подпись под индикатором
     QStringList textFrames_;           // Cписок строк для анимации текстовой части
     int textPaintFraction_;            // Во сколько раз текст будет медленнее анимироваться
     int frames_;                       // Количество кадров и время обновления таймера
     int ringR_;                        // Радиус кольца индикатора
     int ringW_;                        // Толщина кольца индикатора
     uint64_t delayStart_;              // Время задержки перед стартом анимации (мс)
     QColor startColor_;                // Начальный цвет секции индикатора
     QColor endColor_;                  // Конечный цвет секции индикатора
     QColor backgroundColor_;           // Цвет фона
     QMargins margins_;                 // Возможные отступы у виджета, которые закрывать не нужно. По умолчанию равны 0
     bool isAnimatedNow_;               // Хранит информацию о состоянии анимации на данный момент
     QTimer* timer_;                    // Таймер времени отрисовки
     float discreteness_;               // Фактор дискретности (используется для «Ромашки»)
     QElapsedTimer* delayTimer_;        // Таймер для отрисовки с задержкой. Обёртка показывается, но рисуется с медленным
                                        //  затемнением, чтобы избежать мелькание на экране
};
