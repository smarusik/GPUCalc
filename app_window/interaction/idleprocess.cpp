#include "idleprocess.h"
#include "resizeready.h"
#include "dropprocess.h"
#include "window_impl/channelwindow.h"
#include "window_impl/vnaappwindow.h"

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

void IdleProcess::nextState(WinInteractState *sMachine, QDragEnterEvent *event, quint32)
{
    ChannelWindow *dropableWindow=qobject_cast<ChannelWindow *>(event->source());

    if(dropableWindow)
    {
        sMachine->setIState(new DropProcess(qobject_cast<VNAAppWindow*>(sMachine->parentWindow),
                                            dropableWindow));
    }
}
