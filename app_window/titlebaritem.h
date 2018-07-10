#ifndef TITLEBARITEM_H
#define TITLEBARITEM_H

#include "base_nodes/flatcolorrectangularnode.h"
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

    QColor getColor() const;
    void setColor(const QColor &value);

signals:
    void titleBarContentChanged(QQuickItem *titleBarContent);

private:
    virtual QSGNode *updatePaintNode(QSGNode *prev, UpdatePaintNodeData *) override;
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    //mouse events
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void hoverEnterEvent(QHoverEvent *event);
    virtual void hoverLeaveEvent(QHoverEvent *event);

    QColor color;
    FlatColorRectangularNode *bandNode;
    QQuickItem *titleBarContent;
    WinInteractState *interState;
};

#endif // TITLEBARITEM_H
