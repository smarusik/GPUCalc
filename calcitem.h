#ifndef CALCITEM_H
#define CALCITEM_H
#include <QQuickItem>
#include "trianglenode.h"

class CalcItem : public QQuickItem
{
    Q_OBJECT
public:
    CalcItem();

signals:

public slots:

    // QQuickItem interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual QSGNode *updatePaintNode(QSGNode *prev, UpdatePaintNodeData *) override;
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private:
    TriangleNode *triangleNode;
};

#endif // CALCITEM_H
