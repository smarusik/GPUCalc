#include "calcitem.h"
#include <QSGNode>

CalcItem::CalcItem()
{
    setFlag(ItemHasContents, true);
    qDebug()<<"Calc item constructed.";
}


void CalcItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"Double click";
}

QSGNode *CalcItem::updatePaintNode(QSGNode *prev, QQuickItem::UpdatePaintNodeData *)
{
    QSGNode *node=prev;

    if(!node)
    {
        node=new QSGNode;
        triangleNode=new TriangleNode(10, QColor("steelblue"));
        node->appendChildNode(triangleNode);
    }

    triangleNode->updateGeometry(boundingRect());

    return node;
}

void CalcItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}
