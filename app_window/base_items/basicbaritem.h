#ifndef BASICBARITEM_H
#define BASICBARITEM_H

#include "base_nodes/flatcolorrectangularnode.h"
#include <QQuickItem>
#include <QPointer>

class BasicBarItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(quint32 leftIndent READ getLeftIndent WRITE setLeftIndent NOTIFY leftIndentChanged)
    Q_PROPERTY(quint32 rightIndent READ getRightIndent WRITE setRightIndent NOTIFY rightIndentChanged)
    Q_PROPERTY(QQuickItem* barContent READ getBarContent WRITE setBarContent NOTIFY barContentChanged)
public:
    BasicBarItem(QQuickItem *parent=nullptr);

    QQuickItem *getBarContent() const;
    void setBarContent(QQuickItem *value);

    QColor getColor() const;
    void setColor(const QColor &value);

    quint32 getLeftIndent() const;
    void setLeftIndent(const quint32 &value);

    quint32 getRightIndent() const;
    void setRightIndent(const quint32 &value);

signals:
    void barContentChanged(QQuickItem *barContent);
    void colorChanged(const QColor &color);
    void leftIndentChanged(quint32 leftIndent);
    void rightIndentChanged(quint32 rightIndent);

private:
    virtual QSGNode *updatePaintNode(QSGNode *prev, UpdatePaintNodeData *) override;
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    QColor color;
    quint32 leftIndent, rightIndent;
    FlatColorRectangularNode *barNode;
    QPointer<QQuickItem> barContent;
};

#endif // BASICBARITEM_H
