#include "titlebaritem.h"

TitleBarItem::TitleBarItem(QQuickItem *parent):
    BasicBarItem(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
}

void TitleBarItem::mousePressEvent(QMouseEvent *event)
{
    if(interState)
    {
        interState->nextIState(event,BasicInteractState::Move);
    }
}

void TitleBarItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(interState)
    {
        interState->nextIState(event,BasicInteractState::Move);
    }
}

void TitleBarItem::hoverEnterEvent(QHoverEvent *event)
{
    if(interState)
    {
        interState->nextIState(event,BasicInteractState::Move);
    }
}

void TitleBarItem::hoverLeaveEvent(QHoverEvent *event)
{
    if(interState)
    {
        interState->nextIState(event,BasicInteractState::Move);
    }
}

void TitleBarItem::setInterState(WinInteractState *value)
{
    interState = value;
}
