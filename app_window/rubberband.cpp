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

    bandNode=new QSGGeometryNode;

    QSGGeometry *geometry;
    QSGFlatColorMaterial *material;

    geometry=new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),4);
    geometry->setDrawingMode(QSGGeometry::DrawLineLoop);
    geometry->setLineWidth(lineWidth);

    material=new QSGFlatColorMaterial;
    material->setFlag(QSGMaterial::Blending);

    bandNode->setGeometry(geometry);
    bandNode->setMaterial(material);
    bandNode->setFlags(QSGNode::OwnsGeometry|QSGNode::OwnsMaterial,true);
}

void RubberBandItem::setBounds(const QRect &value)
{
    bounds=value;

    QSGGeometry *geometry;
    QSGFlatColorMaterial *material;

    geometry=bandNode->geometry();
    material=(QSGFlatColorMaterial*)bandNode->material();

    QSGGeometry::Point2D* vertices= geometry->vertexDataAsPoint2D();
    qreal x1,y1,x2,y2;
    bounds.getCoords(&x1,&y1,&x2,&y2);
    vertices[0].set(x1,y1);
    vertices[1].set(x2,y1);
    vertices[2].set(x2,y2);
    vertices[3].set(x1,y2);

    material->setColor(Qt::red);

    bandNode->markDirty(QSGNode::DirtyGeometry);
    bandNode->markDirty(QSGNode::DirtyMaterial);

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
