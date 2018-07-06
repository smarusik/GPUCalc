#include "windowstates.h"

WinInteractState::WinInteractState(QQuickWindow *parent) :
    QObject(parent),
    parentWindow(parent)
{
    iState.reset(new OrdinaryState);
}

bool WinInteractState::rearrangeSubwindows()
{
    return iState->rearrangeSubwindows();
}

QCursor WinInteractState::getCursor()
{
    return iState->getCursor();
}

bool WinInteractState::isInResizingState()
{
    return iState->isInResizingState();
}

bool WinInteractState::trackMousePosition(const QPointF &pos)
{
    mousePosition=pos;
}

const QRect &WinInteractState::getStartGeometry()
{
    return startGeometry;
}

bool WinInteractState::updateRubberBand()
{
    return iState->updateRubberBand();
}

void WinInteractState::nextIState(QMouseEvent *event, quint32 hint)
{
    iState->nextState(this,event,hint);
}

void WinInteractState::nextIState(QHoverEvent *event, quint32 hint)
{
    iState->nextState(this,event,hint);
}

void WinInteractState::setIState(BasicInteractState *value)
{
    iState.reset(value);
}

void ResizeReady::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
    if(event->type()&QEvent::MouseButtonPress
            && event->button()&Qt::LeftButton)
    {
        sMachine->setIState(new ResizeProcess(hint));
    }
}

void ResizeReady::nextState(WinInteractState *sMachine, QHoverEvent *event, quint32 hint)
{
    if(event->type()&QEvent::HoverEnter)
    {

    }
    else if(event->type()&QEvent::HoverLeave)
    {
        sMachine->setIState(new OrdinaryState);
    }
}

void OrdinaryState::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
    sMachine->setIState(this);
}

void OrdinaryState::nextState(WinInteractState *sMachine, QHoverEvent *event, quint32 hint)
{
    if(event->type()&QEvent::HoverEnter)
    {
        if(hint&ResizeGen)
        {
            sMachine->setIState(new ResizeReady(hint));
        }
    }
}

QPointF WinInteractState::getMousePosition() const
{
    return mousePosition;
}

void WinInteractState::setStartGeometry(const QRect &value)
{
    startGeometry = value;
}

void ResizeProcess::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
    if(event->type()&QEvent::MouseButtonRelease
            && event->button()&Qt::LeftButton)
    {
        sMachine->setIState(new OrdinaryState);
    }
}
