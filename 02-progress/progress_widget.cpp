#include <progress_widget.h>

#include <QtCore/QtMath>
#include <QtCore/QElapsedTimer>
#include <QtCore/QEvent>
#include <QtCore/QStringList>
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtGui/QPolygon>
#include <QtWidgets/QApplication>


ProgressWidget* ProgressWidget::discrete(
     QWidget* parent
     , const QString& text
     , const QStringList& textAnimation
     , const QColor& start
     , const QColor& end
)
{
     auto progress = new ProgressWidget( parent, text, textAnimation );
     progress->setMode( Mode::Discrete );
     progress->setColor( start, Color::Start );
     progress->setColor( end, Color::End );
     return progress;
}


ProgressWidget* ProgressWidget::solid(
     QWidget* parent
     , const QString& text
     , const QStringList& textAnimation
     , const QColor& start
     , const QColor& end
)
{
     auto progress = new ProgressWidget( parent, text, textAnimation );
     progress->setMode( Mode::Solid );
     progress->setColor( start, Color::Start );
     progress->setColor( end, Color::End );
     return progress;
}


ProgressWidget::ProgressWidget(
     QWidget* parent
     , const QString& text
     , const QStringList& textAnimation
     , bool doStart
)
     : QWidget{ parent }
     , mode_{ Mode::Discrete }
     , text_{ text }
     , textFrames_{ textAnimation }
     , textPaintFraction_( 5 )
     , frames_( 0 )
     , updateInterval_( 40 )
     , ringR_( 22 )
     , ringW_( 18 )
     , delayStart_( 1890 )
     , startColor_( 156, 157, 159 )
     , endColor_( 253, 253, 253 )
     , backgroundColor_( 0, 0, 0, 158 )
     , margins_( QMargins() )
     , isAnimatedNow_( false )
     , timer_( nullptr )
     , discreteness_( 2.5 )
     , delayTimer_( nullptr )
{
     Q_ASSERT( parent );

     setFocusPolicy( Qt::StrongFocus );

     if( parent )
     {
          parent->installEventFilter( this );
          parent->setFocusProxy( this );
     }

     setColor( Qt::white, Color::Text );
     setAutoFillBackground( false );

     if( doStart && parent )
     {
          startAnimation();
     }
     else
     {
          setVisible( false );
     }
}


ProgressWidget::~ProgressWidget()
{
     endAnimation();
}


void ProgressWidget::setColor( const QColor& color, Color colorType )
{
     switch( colorType )
     {
          case Color::Start:
               startColor_ = color;
               break;

          case Color::End:
               endColor_ = color;
               break;

          case Color::Text:
          {
               QPalette pal = palette();
               pal.setColor( QPalette::Text, color );
               setPalette( pal );
          }
          break;

          case Color::Background:
               backgroundColor_ = color;
               break;
     }
}


void ProgressWidget::setMode( const Mode mode )
{
     mode_ = mode;
}


void ProgressWidget::setRingRadius( const int radius )
{
     ringR_ = radius;
}


void ProgressWidget::setRingWidth( const int width )
{
     ringW_ = width;
}


void ProgressWidget::setTextAnimationSpeedFraction( const int textPaintFraction )
{
     textPaintFraction_ = textPaintFraction ? textPaintFraction : 1;
}


void ProgressWidget::startAnimation()
{
     if( isAnimatedNow_ )
     {
          return;
     }
     prepareAndShow();

     if( !timer_ )
     {
          timer_ = new QTimer( this );
          connect( timer_, &QTimer::timeout, this, &ProgressWidget::timerTimeout );
     }
     if( delayStart_ )
     {
          startDelayTimer();
     }
     timer_->start( updateInterval_ );
     update();

     setAnimationState( true );
}


void ProgressWidget::endAnimation()
{
     setAnimationState( false );
     hide();
     if( delayTimer_ )
     {
          delete delayTimer_;
          delayTimer_ = nullptr;
     }
     if( timer_ )
     {
          timer_->stop();
     }
}


void ProgressWidget::setAnimationState( const bool doAnimate )
{
     if( doAnimate == isAnimatedNow_ )
     {
          return;
     }
     isAnimatedNow_ = doAnimate;
}


bool ProgressWidget::eventFilter( QObject* filtered, QEvent* e )
{
     Q_UNUSED( filtered );

     if( !isAnimatedNow_ )
     {
          return false;
     }
     if( e )
     {
          switch( e->type() )
          {
               case QEvent::Resize:
                    resize( static_cast< QResizeEvent* >( e )->size() );
                    setFocus();
                    return false;

               case QEvent::KeyPress:
                    keyPressEvent( static_cast< QKeyEvent* >( e ) );
                    setFocus();
                    return true;

               case QEvent::MouseMove:
               case QEvent::MouseButtonDblClick:
               case QEvent::MouseButtonPress:
               case QEvent::MouseButtonRelease:
                    setFocus();
                    return true;

               default:
                    break;
          }
     }
     return false;
}


void ProgressWidget::paintEvent( QPaintEvent* event )
{
     Q_UNUSED( event );

     QPainter painter{ this };
     painter.setRenderHint( QPainter::Antialiasing );

     // Фон
     QColor bg = backgroundColor_;
     qreal p = 1;

     if( delayTimer_ )
     {
          p = 1.* delayTimer_->elapsed() / delayStart_;

          if( p > 1. )
          {
               p = 1.;
          }
          const QColor transparent = Qt::transparent;

          bg = QColor::fromRgb(
                 static_cast< int >( p * bg.red()   + ( 1 - p ) * transparent.red() )
               , static_cast< int >( p * bg.green() + ( 1 - p ) * transparent.green() )
               , static_cast< int >( p * bg.blue()  + ( 1 - p ) * transparent.blue() )
               , static_cast< int >( p * bg.alpha() + ( 1 - p ) * transparent.alpha() )
               );

          if( delayTimer_->hasExpired( delayStart_ ) )
          {
               delete delayTimer_;
               delayTimer_ = nullptr;
          }
     }

     painter.fillRect(
          margins_.left()
          , margins_.top()
          , width() - margins_.left() - margins_.right()
          , height() - margins_.top() - margins_.bottom()
          , bg
     );
     const qreal showDecorationOpacity = .55;

     if( p < showDecorationOpacity )
     {
          return;
     }
     const float startAngle = ( frames_ * 15 % 360 ) * M_PI / 180;

     if( ringR_ || ringW_ ) //  если есть кольцо
     {
          if( ringR_ < ringW_ / 2 )
          {
               ringR_ = ringW_ / 2;
          }
          painter.save();
          painter.translate( width() / 2 , height() / 2 );

          if( Mode::Discrete == mode_ )
          {
               const int nLines = 2 * M_PI * ( ringR_ + ringW_ * 1. / 2 ) / ( discreteness_ * 4 );
               const auto angle = 2 * M_PI / nLines;

               for( auto i = 0; i < nLines; ++i )
               {
                    QColor clColor(
                           startColor_.red  () + ( endColor_.red  () - startColor_.red  () ) * i / nLines
                         , startColor_.green() + ( endColor_.green() - startColor_.green() ) * i / nLines
                         , startColor_.blue () + ( endColor_.blue () - startColor_.blue () ) * i / nLines
                         , startColor_.alpha() + ( endColor_.alpha() - startColor_.alpha() ) * i / nLines
                         );

                    painter.setPen( QPen( clColor, 4, Qt::SolidLine, Qt::RoundCap ) );
                    painter.drawLine(
                         QPointF(
                                ( ringR_ - ringW_ * 1. / 2 ) * cos( startAngle + i * angle )
                              , ( ringR_ - ringW_ * 1. / 2 ) * sin( startAngle + i * angle )
                              )
                         , QPointF(
                                ( ringR_ + ringW_ * 1. / 2 ) * cos( startAngle + i * angle )
                              , ( ringR_ + ringW_ * 1. / 2 ) * sin( startAngle + i * angle )
                              )
                         );
               }
          }
          else if( Mode::Solid == mode_ )
          {
               const int nLines = 2 * M_PI * ( ringR_ + ringW_ * 1. / 2 );
               const auto angle = 2 * M_PI / nLines;

               for( auto i = 0; i < nLines; ++i )
               {
                    QColor clColor(
                           startColor_.red()   + ( endColor_.red()   - startColor_.red()   ) * i / nLines
                         , startColor_.green() + ( endColor_.green() - startColor_.green() ) * i / nLines
                         , startColor_.blue()  + ( endColor_.blue()  - startColor_.blue()  ) * i / nLines
                         , startColor_.alpha() + ( endColor_.alpha() - startColor_.alpha() ) * i / nLines
                         );

                    painter.setPen( clColor );
                    painter.drawLine(
                         QPointF(
                                ( ringR_ - ringW_ * 1. / 2 ) * cos( startAngle + i * angle )
                              , ( ringR_ - ringW_ * 1. / 2 ) * sin( startAngle + i * angle )
                              )
                         , QPointF(
                                ( ringR_ + ringW_ * 1. / 2 ) * cos( startAngle + i * angle )
                              , ( ringR_ + ringW_ * 1. / 2 ) * sin( startAngle + i * angle )
                              )
                         );
               }
          }
          painter.restore();
     }

     // Текст
     painter.setFont( font() );
     painter.setPen( palette().color( QPalette::Text ) );

     QFontMetrics fm( font() );
     QString txtAdd;

     if( !textFrames_.isEmpty() )
     {
          txtAdd = textFrames_.at( frames_ / textPaintFraction_ % textFrames_.size() );
     }
     QRect textRect ( 0, height() / 2 + ringR_ + fm.height() + 10, width(), height() );
     painter.drawText( textRect,  Qt::AlignHCenter | Qt::AlignTop, text_ + txtAdd );
}


void ProgressWidget::keyPressEvent( QKeyEvent* e )
{
     if( e )
     {
          if( Qt::Key_Escape == e->key() )
          {
               emit cancelled();
               return;
          }
     }
     QWidget::keyPressEvent( e );
}


void ProgressWidget::startDelayTimer()
{
     if( !delayStart_ )
     {
          return;
     }
     delete delayTimer_;
     delayTimer_ = new QElapsedTimer;
     delayTimer_->start();
}


void ProgressWidget::timerTimeout()
{
     ++frames_;
     update();
}


void ProgressWidget::prepareAndShow()
{
     show();
     setFocus();

     if( parentWidget() )
     {
          resize( parentWidget()->size() );
     }
}
