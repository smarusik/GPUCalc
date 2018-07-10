#ifndef FLATCOLORRECTANGULARNODE_H
#define FLATCOLORRECTANGULARNODE_H

#include <QSGGeometryNode>
#include <QColor>

class FlatColorRectangularNode : public QSGGeometryNode
{
public:
    FlatColorRectangularNode();

    QColor getColor() const;
    void setColor(const QColor &value);

    QRectF getBounds() const;
    void setBounds(const QRectF &value);

private:
    QColor color;
    QRectF bounds;
};

#endif // FLATCOLORRECTANGULARNODE_H
