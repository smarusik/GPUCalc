#include "borderitem.h"


BorderItem::BorderItem(QQuickItem *parent, BasicInteractState::StateHint rh):
    BasicContentlessItem(parent),
    resizeHint(rh)
{

}

void BorderItem::hoverEnterEvent(QHoverEvent *event)
{
    interState->nextIState(event,resizeHint);
}

void BorderItem::hoverLeaveEvent(QHoverEvent *event)
{
    interState->nextIState(event,resizeHint);
}

void BorderItem::mousePressEvent(QMouseEvent *event)
{
    interState->nextIState(event,resizeHint);
}

void BorderItem::mouseReleaseEvent(QMouseEvent *event)
{
    interState->nextIState(event,resizeHint);
}
