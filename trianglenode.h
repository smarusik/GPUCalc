#ifndef TRIANGLENODE_H
#define TRIANGLENODE_H

#include <QSGGeometryNode>

class TriangleNode : public QSGGeometryNode
{
public:
    TriangleNode(float size,const QColor &color);

    void updateGeometry(const QRectF &bounds);

private:
    QSGGeometry m_geometry;

};

#endif // TRIANGLENODE_H
