#include "basiccontentlessitem.h"

BasicContentlessItem::BasicContentlessItem(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, false);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setParentItem(parent);

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
