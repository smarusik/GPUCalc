#include "basicbaritem.h"

BasicBarItem::BasicBarItem(QQuickItem *parent):
    QQuickItem(parent),
    leftIndent(0),
    rightIndent(0)
{
    setFlag(ItemHasContents, true);
    setAcceptHoverEvents(false);
    setAcceptedMouseButtons(Qt::NoButton);

    barNode=new FlatColorRectangularNode;
    barNode->geometry()->setDrawingMode(GL_QUADS);

}

QQuickItem *BasicBarItem::getBarContent() const
{
    return barContent;
}

void BasicBarItem::setBarContent(QQuickItem *value)
{
    barContent=value;
    barContent->setParentItem(this);
    barContent->setAcceptedMouseButtons(Qt::NoButton);
    barContent->setAcceptHoverEvents(false);

}

QColor BasicBarItem::getColor() const
{
    return color;
}

void BasicBarItem::setColor(const QColor &value)
{
    color = value;
    barNode->setColor(color);
}

quint32 BasicBarItem::getLeftIndent() const
{
    return leftIndent;
}

void BasicBarItem::setLeftIndent(const quint32 &value)
{
    leftIndent = value;
}

quint32 BasicBarItem::getRightIndent() const
{
    return rightIndent;
}

void BasicBarItem::setRightIndent(const quint32 &value)
{
    rightIndent = value;
}

QSGNode *BasicBarItem::updatePaintNode(QSGNode *prev, QQuickItem::UpdatePaintNodeData *)
{
    QSGNode *oldNode=prev;

    if(!oldNode)
    {
        oldNode=new QSGNode;
        oldNode->appendChildNode(barNode);
    }

    return oldNode;
}

void BasicBarItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    barNode->setBounds(QRectF(QPointF(0,0), newGeometry.size()));
    if(barContent)
    {
        barContent->setPosition(QPointF(leftIndent,0));
        barContent->setSize(QSizeF(size().width()-leftIndent-rightIndent,size().height()));
    }

    update();
}
