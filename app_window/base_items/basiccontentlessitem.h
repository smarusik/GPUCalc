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

    // QQuickItem interface
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
};

#endif // BASICCONTENTLESSITEM_H
