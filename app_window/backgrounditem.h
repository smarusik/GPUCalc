#ifndef CALCITEM_H
#define CALCITEM_H

#include "windowstates.h"
#include <QQuickItem>

class BackgroundItem : public QQuickItem
{
    Q_OBJECT
public:
    BackgroundItem();

    void setInterState(WinInteractState *value);

private:
    virtual QSGNode *updatePaintNode(QSGNode *prev, UpdatePaintNodeData *) override;
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    QColor color;
    WinInteractState *interState;
};

#endif // CALCITEM_H
