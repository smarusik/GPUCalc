#ifndef WORKAREAITEM_H
#define WORKAREAITEM_H

#include "base_items/basiccontentlessitem.h"

class BorderItem: public BasicContentlessItem
{
public:
    BorderItem(QQuickItem *parent,
               BasicInteractState::StateHint rh
               );

    virtual void hoverEnterEvent(QHoverEvent *event);

    virtual void hoverLeaveEvent(QHoverEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    BasicInteractState::StateHint resizeHint;
};

#endif // WORKAREAITEM_H
