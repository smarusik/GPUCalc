#ifndef TITLEBARITEM_H
#define TITLEBARITEM_H

#include "base_items/basicbaritem.h"
#include "interaction/wininteractstate.h"

class TitleBarItem : public BasicBarItem
{
    Q_OBJECT

public:
    TitleBarItem(QQuickItem *parent=nullptr);

    void setInterState(WinInteractState *value);

private:

    //mouse events
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void hoverEnterEvent(QHoverEvent *event);
    virtual void hoverLeaveEvent(QHoverEvent *event);

    QPointer<WinInteractState> interState;
};

#endif // TITLEBARITEM_H
