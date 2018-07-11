#include "basiccontentlessitem.h"

BasicContentlessItem::BasicContentlessItem(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, false);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setParentItem(parent);

    setFlag(QQuickItem::ItemAcceptsDrops);

    startTimer(100);
}

void BasicContentlessItem::mousePressEvent(QMouseEvent *event)
{
    interState->nextIState(event);
}

void BasicContentlessItem::mouseReleaseEvent(QMouseEvent *event)
{

}

void BasicContentlessItem::hoverEnterEvent(QHoverEvent *event)
{
    interState->nextIState(event);
}

void BasicContentlessItem::hoverLeaveEvent(QHoverEvent *event)
{
    interState->nextIState(event);
}

void BasicContentlessItem::setInterState(WinInteractState *value)
{
    interState = value;
}

void BasicContentlessItem::timerEvent(QTimerEvent *)
{
}


void BasicContentlessItem::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<event;
}

void BasicContentlessItem::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug()<<event;
}

void BasicContentlessItem::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug()<<event;
}
