#include "titlebaritem.h"

TitleBarItem::TitleBarItem(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);

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

void TitleBarItem::setInterState(WinInteractState *value)
{
    interState = value;
}
