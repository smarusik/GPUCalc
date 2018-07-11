#ifndef WORKAREAITEM_H
#define WORKAREAITEM_H

#include "base_items/basiccontentlessitem.h"

class BorderItem: public BasicContentlessItem
{
public:
    BorderItem(QQuickItem *parent,
               BasicInteractState::StateHint rh
               ):
        BasicContentlessItem(parent),
        resizeHint(rh)
    {

    }

    virtual void hoverEnterEvent(QHoverEvent *event)
    {
        interState->nextIState(event,resizeHint);
    }

    virtual void hoverLeaveEvent(QHoverEvent *event)
    {
        interState->nextIState(event,resizeHint);
    }

    virtual void mousePressEvent(QMouseEvent *event)
    {
        interState->nextIState(event,resizeHint);
    }

    virtual void mouseReleaseEvent(QMouseEvent *event)
    {
        interState->nextIState(event,resizeHint);
    }

private:
    BasicInteractState::StateHint resizeHint;
};

#endif // WORKAREAITEM_H
