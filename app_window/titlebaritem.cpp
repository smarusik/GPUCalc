#include "titlebaritem.h"

TitleBarItem::TitleBarItem(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    bandNode=new FlatColorRectangularNode;
    bandNode->geometry()->setDrawingMode(GL_QUADS);

}

QQuickItem *TitleBarItem::getTitleBarContent() const
{
    return titleBarContent;
}

void TitleBarItem::setTitleBarContent(QQuickItem *value)
{
    titleBarContent=value;
    titleBarContent->setParentItem(this);
}

void TitleBarItem::mousePressEvent(QMouseEvent *event)
{
    interState->nextIState(event,BasicInteractState::Move);
}

void TitleBarItem::mouseReleaseEvent(QMouseEvent *event)
{
    interState->nextIState(event,BasicInteractState::Move);
}

void TitleBarItem::hoverEnterEvent(QHoverEvent *event)
{
    interState->nextIState(event,BasicInteractState::Move);
}

void TitleBarItem::hoverLeaveEvent(QHoverEvent *event)
{
    interState->nextIState(event,BasicInteractState::Move);
}

QColor TitleBarItem::getColor() const
{
    return color;
}

void TitleBarItem::setColor(const QColor &value)
{
    color = value;
    bandNode->setColor(color);
}

QSGNode *TitleBarItem::updatePaintNode(QSGNode *prev, QQuickItem::UpdatePaintNodeData *)
{
    QSGNode *oldNode=prev;

    if(!oldNode)
    {
        oldNode=new QSGNode;
        oldNode->appendChildNode(bandNode);
    }

    return oldNode;
}

void TitleBarItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    bandNode->setBounds(QRectF(QPointF(0,0), newGeometry.size()));

    update();
}

void TitleBarItem::setInterState(WinInteractState *value)
{
    interState = value;
}
