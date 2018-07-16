#include "idleprocess.h"
#include "resizeready.h"

IdleProcess::IdleProcess()
{
    cursor=QCursor(Qt::ArrowCursor);
}

void IdleProcess::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
    sMachine->setIState(this);
}

void IdleProcess::nextState(WinInteractState *sMachine, QHoverEvent *event, quint32 hint)
{
    if(event->type()&QEvent::HoverEnter)
    {
        if(hint&ResizeGeneral || hint&Move)
        {
            sMachine->setIState(new ResizeReady(hint));
        }
    }
}
