#include "contentlessitems.h"

BaseContentlessItem::BaseContentlessItem(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, false);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setParentItem(parent);

    startTimer(100);
}

void BaseContentlessItem::mousePressEvent(QMouseEvent *event)
{
    interState->nextIState(event);
}

void BaseContentlessItem::mouseReleaseEvent(QMouseEvent *event)
{

}

void BaseContentlessItem::hoverEnterEvent(QHoverEvent *event)
{
    interState->nextIState(event);
}

void BaseContentlessItem::hoverLeaveEvent(QHoverEvent *event)
{
    interState->nextIState(event);
}

void BaseContentlessItem::setInterState(WinInteractState *value)
{
    interState = value;
}

void BaseContentlessItem::timerEvent(QTimerEvent *)
{
}
