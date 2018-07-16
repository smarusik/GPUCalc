#include "modificationconfirmaton.h"
#include "moveprocess.h"
#include "resizeprocess.h"
#include "dragprocess.h"

BaseConfirmation::BaseConfirmation(quint32 hint, const QPoint &chkPt):
    ResizeReady(hint),
    confirmCheckPoint(chkPt)
{
}

bool BaseConfirmation::checkPositionDelta(const QPoint &pos)
{
    return (pos-confirmCheckPoint).manhattanLength()>10;
}

ResizeConfirmaton::ResizeConfirmaton(quint32 hint, const QPoint &chkPt):
    BaseConfirmation(hint,chkPt)
{

}

void ResizeConfirmaton::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 )
{
    if(event->type()==QMouseEvent::MouseButtonRelease)
    {
        sMachine->setIState(new ResizeReady(direction));
        return;
    }

    sMachine->setIState(new ResizeProcess(direction,sMachine->parentWindow));
    sMachine->trackMousePosition(event->screenPos());
}

MoveConfirmation::MoveConfirmation(const QPoint &chkPt):
    BaseConfirmation(BasicInteractState::Move,chkPt)
{
    cursor=Qt::ClosedHandCursor;
}

void MoveConfirmation::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 )
{
    if(event->type()==QMouseEvent::MouseButtonRelease)
    {
        sMachine->setIState(new ResizeReady(BasicInteractState::Move));
        return;
    }

    sMachine->setIState(new MoveProcess(direction,sMachine->parentWindow));
    sMachine->trackMousePosition(event->screenPos());
}

DragConfirmation::DragConfirmation(const QPoint &chkPt):
    BaseConfirmation(BasicInteractState::Drag,chkPt)
{
    cursor=Qt::DragMoveCursor;
}

void DragConfirmation::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32)
{
    if(event->type()==QMouseEvent::MouseButtonRelease)
    {
        sMachine->setIState(new ResizeReady(BasicInteractState::Drag));
        return;
    }

    sMachine->setIState(new DragProcess(direction,sMachine->parentWindow));
    sMachine->trackMousePosition(event->screenPos());
}
