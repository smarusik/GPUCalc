#ifndef RUBBERBAND_H
#define RUBBERBAND_H

#include "base_nodes/flatcolorrectangularnode.h"
#include <QQuickItem>
#include <QQuickWindow>

class RubberBandItem : public QQuickItem
{
    Q_OBJECT
public:
    RubberBandItem(QQuickItem *parent=nullptr);

    void setBounds(const QRect &value);

private:
    virtual QSGNode *updatePaintNode(QSGNode *prev, UpdatePaintNodeData *) override;
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    QRectF bounds;
    FlatColorRectangularNode *bandNode;
    static constexpr quint16 lineWidth=2;
};

#endif // RUBBERBAND_H
