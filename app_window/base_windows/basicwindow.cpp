#include "basicwindow.h"
#include "interaction/idleprocess.h"

BasicWindow::BasicWindow(QWindow *parent):
    QQuickWindow(parent),
    interState(this)
{
    setColor(Qt::transparent);
    setDefaults();

    interState.setIState(new IdleProcess);

    background=new BackgroundItem;
    background->setParentItem(contentItem());
    background->setPosition(QPointF(0,0));
    background->setInterState(&interState);
    background->setColor(Qt::gray);

    workingArea=new BasicContentlessItem(background);
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
    if(!interState.isInResizingState())
    {
        resizeInternals(event->size());
        moveInternals(QPoint(0,0));
    }
}

void BasicWindow::moveEvent(QMoveEvent *event)
{
    if(interState.isInResizingState())
    {
        moveInternals(-event->pos()+event->oldPos());
    }
}


void BasicWindow::mousePressEvent(QMouseEvent *event)
{
    QQuickWindow::mousePressEvent(event);
}

void BasicWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QQuickWindow::mouseReleaseEvent(event);
}

void BasicWindow::mouseMoveEvent(QMouseEvent *event)
{
    interState.trackMousePosition(event->globalPos());
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
    statusBarHeight=20;
}

void BasicWindow::resizeInternals(const QSize &bgSize)
{
    background->setSize(bgSize);
    workingArea->setSize(background->size()-2*QSizeF(frameWidth,frameWidth));

    if(titleBar)
    {
        titleBar->setSize(QSizeF(background->width()-2*frameWidth,titleBarHeight));
        workingArea->setHeight(workingArea->height()-titleBarHeight);
    }

    if(statusBar)
    {
        statusBar->setSize(QSizeF(background->width()-2*frameWidth,statusBarHeight));
        workingArea->setHeight(workingArea->height()-statusBarHeight);
    }

    lBorder->setSize(QSizeF(frameWidth,bgSize.height()-frameWidth*4));
    rBorder->setSize(lBorder->size());
    tBorder->setSize(QSizeF(bgSize.width()-frameWidth*4,frameWidth));
    bBorder->setSize(tBorder->size());

    QSizeF cornerSize(frameWidth*2,frameWidth*2);
    ltCorner->setSize(cornerSize);
    rtCorner->setSize(cornerSize);
    lbCorner->setSize(cornerSize);
    rbCorner->setSize(cornerSize);
}

void BasicWindow::moveInternals(const QPoint &bgOrigin)
{
    background->setPosition(bgOrigin);
    workingArea->setPosition(QPointF(frameWidth,frameWidth));

    if(titleBar)
    {
        titleBar->setPosition(QPointF(frameWidth,frameWidth));
        workingArea->setPosition(workingArea->position()+QPointF(0,titleBarHeight));
    }

    if(statusBar)
    {
        statusBar->setPosition(QPointF(frameWidth,background->height()-frameWidth-statusBar->height()));
    }

    lBorder->setPosition(QPointF(0,frameWidth*2));
    rBorder->setPosition(lBorder->position()+QPointF(background->width()-frameWidth,0));
    tBorder->setPosition(QPointF(frameWidth*2,0));
    bBorder->setPosition(tBorder->position()+QPointF(0,background->height()-frameWidth));
    ltCorner->setPosition(QPointF(0,0));
    rtCorner->setPosition(QPointF(background->width()-frameWidth*2,0));
    lbCorner->setPosition(QPointF(0,background->height()-frameWidth*2));
    rbCorner->setPosition(QPointF(background->width()-frameWidth*2,background->height()-frameWidth*2));
}

StatusBarItem *BasicWindow::getStatusBar() const
{
    return statusBar;
}

void BasicWindow::setStatusBar(StatusBarItem *value)
{
    statusBar = value;
    statusBar->setParentItem(background);
}

void BasicWindow::timerEvent(QTimerEvent *)
{
    setCursor(interState.getCursor());
    interState.updateRubberBand();
}

TitleBarItem *BasicWindow::getTitleBar() const
{
    return titleBar;
}

void BasicWindow::setTitleBar(TitleBarItem *value)
{
    titleBar = value;
    titleBar->setParentItem(background);
    titleBar->setInterState(&interState);
}
