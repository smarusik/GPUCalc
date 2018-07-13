#ifndef CALCITEM_H
#define CALCITEM_H

#include "base_nodes/flatcolorrectangularnode.h"
#include "interaction/wininteractstate.h"
#include <QQuickItem>

class BackgroundItem : public QQuickItem
{
    Q_OBJECT
public:
    BackgroundItem(QQuickItem *parent=nullptr);

    void setInterState(WinInteractState *value);

    QColor getColor() const;
    void setColor(const QColor &value);

private:
    virtual QSGNode *updatePaintNode(QSGNode *prev, UpdatePaintNodeData *) override;
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    QColor color;
    QSizeF bounds;
    WinInteractState *interState;
    FlatColorRectangularNode *node;
};

#endif // CALCITEM_H
