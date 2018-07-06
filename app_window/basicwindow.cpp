#include "basicwindow.h"

BasicWindow::BasicWindow(QWindow *parent):
    QQuickWindow(parent),
    interState(this)
{
    setPosition(QPoint(100,100));

    setColor(Qt::transparent);
    setDefaults();

    interState.setIState(new OrdinaryState);

    background=new BackgroundItem;
    background->setParentItem(contentItem());
    background->setPosition(QPointF(0,0));
    background->setInterState(&interState);

    workingArea=new BaseContentlessItem(background);
    workingArea->setInterState(&interState);

    lBorder=new BorderItem(background,BasicInteractState::ResizeLeft);
    lBorder->setInterState(&interState);
    rBorder=new BorderItem(background,BasicInteractState::ResizeRight);
    rBorder->setInterState(&interState);
    tBorder=new BorderItem(background,BasicInteractState::ResizeTop);
    tBorder->setInterState(&interState);
    bBorder=new BorderItem(background,BasicInteractState::ResizeBottom);
    bBorder->setInterState(&interState);

    lbCorner=new BorderItem(background,BasicInteractState::ResizeLeftBottom);
    lbCorner->setInterState(&interState);
    rtCorner=new BorderItem(background,BasicInteractState::ResizeRightTop);
    rtCorner->setInterState(&interState);
    ltCorner=new BorderItem(background,BasicInteractState::ResizeLeftTop);
    ltCorner->setInterState(&interState);
    rbCorner=new BorderItem(background,BasicInteractState::ResizeRightBottom);
    rbCorner->setInterState(&interState);

    setFlag(Qt::CustomizeWindowHint, true);
    setFlag(Qt::WindowTitleHint, false);
    setFlag(Qt::FramelessWindowHint, true);

    startTimer(100);
}

void BasicWindow::resizeEvent(QResizeEvent *event)
{
    QSize backgroundSize;

    if(interState.isInResizingState())
    {
        backgroundSize=interState.getStartGeometry().size();

        if(!rubberBand)
        {
            rubberBand.reset(new RubberBandItem(contentItem()));
        }

        rubberBand->setBounds(QRect(0,0,size().width(),size().height()));
    }
    else
    {
        backgroundSize=event->size();
        resizeInternals(backgroundSize);
        interState.setStartGeometry(geometry());
    }
}

void BasicWindow::moveEvent(QMoveEvent *event)
{
    QQuickWindow::moveEvent(event);
}



void BasicWindow::mousePressEvent(QMouseEvent *event)
{
    QQuickWindow::mousePressEvent(event);
}

void BasicWindow::mouseReleaseEvent(QMouseEvent *event)
{
    interState.nextIState(event);
    if(!interState.updateRubberBand())
    {
        setGeometry(QRect(interState.getStartGeometry().topLeft(),
                    interState.getMousePosition().toPoint()));

        qDebug()<<QRect(interState.getStartGeometry().topLeft(),
                        interState.getMousePosition().toPoint());
    }

    QQuickWindow::mouseReleaseEvent(event);
}

void BasicWindow::mouseMoveEvent(QMouseEvent *event)
{
    interState.trackMousePosition(event->screenPos());
    QQuickWindow::mouseMoveEvent(event);
}

bool BasicWindow::event(QEvent *event)
{
    return QQuickWindow::event(event);
}

void BasicWindow::setDefaults()
{
    frameWidth=5;
    titleBarHeight=20;
}

void BasicWindow::resizeInternals(const QSize &backgroundSize)
{
    rubberBand.reset();

    background->setPosition(contentItem()->position());
    background->setSize(backgroundSize);

    workingArea->setPosition(background->position()+QPointF(frameWidth,frameWidth));
    workingArea->setSize(background->size()-2*QSizeF(frameWidth,frameWidth));

    if(titleBar)
    {
        titleBar->setPosition(background->position()+QPointF(frameWidth,frameWidth));
        titleBar->setSize(QSizeF(background->width()-2*frameWidth,titleBarHeight));
    }

    lBorder->setPosition(QPointF(0,frameWidth*2));
    lBorder->setSize(QSizeF(frameWidth,backgroundSize.height()-frameWidth*4));

    rBorder->setPosition(lBorder->position()+QPointF(backgroundSize.width()-frameWidth,0));
    rBorder->setSize(lBorder->size());

    tBorder->setPosition(QPointF(frameWidth*2,0));
    tBorder->setSize(QSizeF(backgroundSize.width()-frameWidth*4,frameWidth));

    bBorder->setPosition(tBorder->position()+QPointF(0,backgroundSize.height()-frameWidth));
    bBorder->setSize(tBorder->size());

    QSizeF cornerSize(frameWidth*2,frameWidth*2);

    ltCorner->setPosition(QPointF(0,0));
    ltCorner->setSize(cornerSize);

    rtCorner->setPosition(QPointF(backgroundSize.width()-frameWidth*2,0));
    rtCorner->setSize(cornerSize);

    lbCorner->setPosition(QPointF(0,backgroundSize.height()-frameWidth*2));
    lbCorner->setSize(cornerSize);

    rbCorner->setPosition(QPointF(backgroundSize.width()-frameWidth*2,backgroundSize.height()-frameWidth*2));
    rbCorner->setSize(cornerSize);
}

BaseContentlessItem *BasicWindow::getWorkingArea() const
{
    return workingArea;
}

void BasicWindow::setWorkingArea(BaseContentlessItem *value)
{
    workingArea = value;
    workingArea->setParentItem(background);
    workingArea->setVisible(true);
}

void BasicWindow::timerEvent(QTimerEvent *)
{
    setCursor(interState.getCursor());
}

QQuickItem *BasicWindow::getTitleBar() const
{
    return titleBar;
}

void BasicWindow::setTitleBar(QQuickItem *value)
{
    titleBar = value;
    titleBar->setParentItem(contentItem());
    titleBar->setVisible(true);
}
