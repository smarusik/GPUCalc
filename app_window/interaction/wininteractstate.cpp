#include "wininteractstate.h"
#include "idleprocess.h"

WinInteractState::WinInteractState(QQuickWindow *parent) :
    QObject(parent),
    parentWindow(parent)
{
    iState.reset(new IdleProcess);
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

void WinInteractState::trackMousePosition(const QPointF &pos)
{
    iState->trackMousePosition(pos);
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

void WinInteractState::setStartGeometry(const QRect &value)
{
    startGeometry = value;
}
