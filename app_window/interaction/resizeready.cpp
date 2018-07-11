#include "resizeready.h"
#include "moveprocess.h"
#include "resizeprocess.h"
#include "idleprocess.h"

ResizeReady::ResizeReady(quint32 hint)
{
    direction=hint;

    if(direction&ResizeHorizontal)
        cursor=Qt::SizeHorCursor;
    else if(direction&ResizeVertical)
        cursor=Qt::SizeVerCursor;
    else if(direction&ResizeDiagLeft)
        cursor=Qt::SizeBDiagCursor;
    else if(direction&ResizeDiagRight)
        cursor=Qt::SizeFDiagCursor;
    else if(direction&Move)
        cursor=Qt::OpenHandCursor;
    else
        cursor=Qt::ArrowCursor;
}

void ResizeReady::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
    if(event->type()&QEvent::MouseButtonPress
            && event->button()&Qt::LeftButton)
    {
        if(hint&Move)
        {
            sMachine->setIState(new MoveProcess(hint,sMachine->parentWindow));
        }
        else if(hint&ResizeGen)
        {
            sMachine->setIState(new ResizeProcess(hint,sMachine->parentWindow));
        }
        sMachine->trackMousePosition(event->screenPos());
    }
}

void ResizeReady::nextState(WinInteractState *sMachine, QHoverEvent *event, quint32 hint)
{
    if(event->type()&QEvent::HoverEnter)
    {

    }
    else if(event->type()&QEvent::HoverLeave)
    {
        sMachine->setIState(new IdleProcess);
    }
}
