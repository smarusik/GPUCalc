#include "backgrounditem.h"
#include <QSGNode>
#include <QSGFlatColorMaterial>

BackgroundItem::BackgroundItem():
color(Qt::gray)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);

    startTimer(100);
}

QSGNode *BackgroundItem::updatePaintNode(QSGNode *prev, QQuickItem::UpdatePaintNodeData *)
{
    QSGGeometryNode *node=(QSGGeometryNode*)prev;
    QSGGeometry *geometry;
    QSGFlatColorMaterial *material;

    if(!node)
    {
        QSGGeometryNode *newNode=new QSGGeometryNode;

        geometry=new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),4);
        geometry->setDrawingMode(GL_QUADS);
        newNode->setGeometry(geometry);

        material=new QSGFlatColorMaterial;
        newNode->setMaterial(material);

        node=newNode;
        node->setFlags(QSGNode::OwnsGeometry|QSGNode::OwnsMaterial,true);
    }
    else
    {
        geometry=node->geometry();
        material=(QSGFlatColorMaterial*)node->material();
    }

    QSGGeometry::Point2D* vertices= geometry->vertexDataAsPoint2D();
    vertices[0].set(0,0);
    vertices[1].set(width(),0);
    vertices[2].set(width(),height());
    vertices[3].set(0,height());

    material->setColor(color);

    return node;
}

void BackgroundItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    update();
}

void BackgroundItem::timerEvent(QTimerEvent *)
{
    return;
}

void BackgroundItem::setInterState(WinInteractState *value)
{
    interState = value;
}
