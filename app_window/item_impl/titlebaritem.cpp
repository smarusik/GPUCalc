#include "titlebaritem.h"

TitleBarItem::TitleBarItem(QQuickItem *parent):
    BasicBarItem(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
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
