#include "flatcolorrectangularnode.h"
#include <QSGFlatColorMaterial>

FlatColorRectangularNode::FlatColorRectangularNode()
{
    QSGGeometry *geom;
    QSGFlatColorMaterial *mat;

    geom=new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),4);

    mat=new QSGFlatColorMaterial;
    mat->setFlag(QSGMaterial::Blending);

    setGeometry(geom);
    setMaterial(mat);
    setFlags(QSGNode::OwnsGeometry|QSGNode::OwnsMaterial,true);
}

QColor FlatColorRectangularNode::getColor() const
{
    return color;
}

void FlatColorRectangularNode::setColor(const QColor &value)
{
    color = value;
    QSGFlatColorMaterial *mat;
    mat=(QSGFlatColorMaterial*)material();
    mat->setColor(color);

    markDirty(QSGNode::DirtyMaterial);
}

QRectF FlatColorRectangularNode::getBounds() const
{
    return bounds;
}

void FlatColorRectangularNode::setBounds(const QRectF &value)
{
    bounds=value;

    QSGGeometry *geom;

    geom=geometry();

    QSGGeometry::Point2D* vertices= geom->vertexDataAsPoint2D();
    qreal x1,y1,x2,y2;
    bounds.getCoords(&x1,&y1,&x2,&y2);
    vertices[0].set(x1,y1);
    vertices[1].set(x2,y1);
    vertices[2].set(x2,y2);
    vertices[3].set(x1,y2);

    markDirty(QSGNode::DirtyGeometry);
}
