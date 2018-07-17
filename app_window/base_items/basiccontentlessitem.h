#ifndef BASICCONTENTLESSITEM_H
#define BASICCONTENTLESSITEM_H

#include "interaction/wininteractstate.h"
#include <QQuickItem>

class BasicContentlessItem : public QQuickItem
{
    Q_OBJECT
public:
    BasicContentlessItem(QQuickItem *parent=nullptr);

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

#endif // BASICCONTENTLESSITEM_H
