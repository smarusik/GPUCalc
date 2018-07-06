#ifndef WORKAREAITEM_H
#define WORKAREAITEM_H

#include "windowstates.h"
#include <QQuickItem>

class BaseContentlessItem : public QQuickItem
{
    Q_OBJECT
public:
    BaseContentlessItem(QQuickItem *parent=nullptr);

    void setInterState(WinInteractState *value);

protected:
    virtual void timerEvent(QTimerEvent *);

    //mouse events
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void hoverEnterEvent(QHoverEvent *event);
    virtual void hoverLeaveEvent(QHoverEvent *event);

    WinInteractState *interState;
};

class BorderItem: public BaseContentlessItem
{
public:
    BorderItem(QQuickItem *parent,
               BasicInteractState::StateHint rh
               ):
        BaseContentlessItem(parent),
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

    virtual void mouseMoveEvent(QMouseEvent *event)
    {

    }

private:
    BasicInteractState::StateHint resizeHint;
};

#endif // WORKAREAITEM_H
