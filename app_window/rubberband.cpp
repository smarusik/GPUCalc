#include "rubberband.h"
#include <QSGNode>
#include <QSGFlatColorMaterial>

RubberBandItem::RubberBandItem(QQuickItem *parent):
    QQuickItem(parent)
{
    setParentItem(parent);
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::NoButton);
    setAcceptHoverEvents(false);

    bandNode=new FlatColorRectangularNode;
    bandNode->geometry()->setDrawingMode(QSGGeometry::DrawLineLoop);
    bandNode->geometry()->setLineWidth(lineWidth);
    bandNode->setColor(Qt::red);
}

void RubberBandItem::setBounds(const QRect &value)
{
    bounds=value;
    bandNode->setBounds(bounds);

    update();
}

QSGNode *RubberBandItem::updatePaintNode(QSGNode *prev, QQuickItem::UpdatePaintNodeData *)
{
    QSGNode *node=prev;

    if(!node)
    {
        node=new QSGNode;
        node->appendChildNode(bandNode);
    }

    return node;
}

void RubberBandItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry,oldGeometry);
}
