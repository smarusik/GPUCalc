#ifndef TITLEBARITEM_H
#define TITLEBARITEM_H

#include "windowstates.h"
#include <QQuickItem>

class TitleBarItem : public QQuickItem
{
    Q_OBJECT

public:
    TitleBarItem(QQuickItem *parent=nullptr);

    void setInterState(WinInteractState *value);

    QQuickItem *getTitleBarContent() const;
    void setTitleBarContent(QQuickItem *value);

signals:
    void titleBarContentChanged(QQuickItem *titleBarContent);

private:
    //mouse events
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void hoverEnterEvent(QHoverEvent *event);
    virtual void hoverLeaveEvent(QHoverEvent *event);

    QQuickItem *titleBarContent;
    WinInteractState *interState;
};

#endif // TITLEBARITEM_H
