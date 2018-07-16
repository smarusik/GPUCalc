#include "modificationconfirmaton.h"
#include "moveprocess.h"
#include "resizeprocess.h"

BaseConfirmaton::BaseConfirmaton(quint32 hint, const QPoint &chkPt):
    ResizeReady(hint),
    resizeCheckPoint(chkPt)
{
}

bool BaseConfirmaton::checkPositionDelta(const QPoint &pos)
{
    return (pos-resizeCheckPoint).manhattanLength()>10;
}

ResizeConfirmaton::ResizeConfirmaton(quint32 hint, const QPoint &chkPt):
    BaseConfirmaton(hint,chkPt)
{

}

void ResizeConfirmaton::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 )
{
    sMachine->setIState(new ResizeProcess(direction,sMachine->parentWindow));
    sMachine->trackMousePosition(event->screenPos());
}

MoveConfirmaton::MoveConfirmaton(const QPoint &chkPt):
    BaseConfirmaton(BasicInteractState::Move,chkPt)
{
    cursor=Qt::ClosedHandCursor;
}

void MoveConfirmaton::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 )
{
    sMachine->setIState(new MoveProcess(direction,sMachine->parentWindow));
    sMachine->trackMousePosition(event->screenPos());
}
