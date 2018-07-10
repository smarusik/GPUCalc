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
    background->setColor(Qt::gray);

    workingArea=new BaseContentlessItem(background);
    workingArea->setInterState(&interState);

    titleBar=new TitleBarItem(background);
    titleBar->setColor(Qt::blue);
    titleBar->setInterState(&interState);

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

void BasicWindow::resizeInternals(const QSize &bgSize)
{
    background->setSize(bgSize);
    workingArea->setSize(background->size()-2*QSizeF(frameWidth,frameWidth));

    titleBar->setSize(QSizeF(background->width()-2*frameWidth,titleBarHeight));

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
    workingArea->setPosition(QPointF(frameWidth,frameWidth+titleBarHeight));
    titleBar->setPosition(QPointF(frameWidth,frameWidth));
    lBorder->setPosition(QPointF(0,frameWidth*2));
    rBorder->setPosition(lBorder->position()+QPointF(background->width()-frameWidth,0));
    tBorder->setPosition(QPointF(frameWidth*2,0));
    bBorder->setPosition(tBorder->position()+QPointF(0,background->height()-frameWidth));
    ltCorner->setPosition(QPointF(0,0));
    rtCorner->setPosition(QPointF(background->width()-frameWidth*2,0));
    lbCorner->setPosition(QPointF(0,background->height()-frameWidth*2));
    rbCorner->setPosition(QPointF(background->width()-frameWidth*2,background->height()-frameWidth*2));
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
    interState.updateRubberBand();
}

QQuickItem *BasicWindow::getTitleBarContent() const
{
    return titleBarContent;
}

void BasicWindow::setTitleBarContent(QQuickItem *value)
{
    titleBarContent = value;
    titleBarContent->setParentItem(titleBar);
    titleBarContent->setVisible(true);
}
