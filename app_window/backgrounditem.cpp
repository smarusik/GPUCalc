#include "backgrounditem.h"
#include <QSGNode>
#include <QSGFlatColorMaterial>

BackgroundItem::BackgroundItem():
color(Qt::gray)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);

    node=new FlatColorRectangularNode;
    node->geometry()->setDrawingMode(GL_QUADS);

    startTimer(100);
}

QSGNode *BackgroundItem::updatePaintNode(QSGNode *prev, QQuickItem::UpdatePaintNodeData *)
{
    QSGNode *oldNode=prev;

    if(!oldNode)
    {
        oldNode=new QSGNode;
        oldNode->appendChildNode(node);
    }

    return oldNode;
}

void BackgroundItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    node->setBounds(QRectF(QPointF(0,0), newGeometry.size()));
}

QColor BackgroundItem::getColor() const
{
    return color;
}

void BackgroundItem::setColor(const QColor &value)
{
    color = value;
    node->setColor(color);
}

void BackgroundItem::setInterState(WinInteractState *value)
{
    interState = value;
}
