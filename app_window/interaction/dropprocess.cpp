#include "dropprocess.h"
#include "idleprocess.h"
#include "window_impl/vnaappwindow.h"

DropProcess::DropProcess(VNAAppWindow *bW, BasicWindow *dW):
    appWindow(bW),
    dropWindow(dW)
{
    rubberBand.reset(new RubberBandItem());
    appWindow->addDockable(rubberBand.data());
}

void DropProcess::trackMousePosition(const QPointF &)
{
    return;
}

bool DropProcess::updateRubberBand()
{
    if(!rubberBand)
    {
        return false;
    }

    return appWindow->arrangeDockables();
}

bool DropProcess::isInResizingState()
{
    false;
}

void DropProcess::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
    if(event->type()&QEvent::MouseButtonRelease
            && event->button()&Qt::RightButton)
    {
        sMachine->setIState(new IdleProcess);
    }
}

void DropProcess::nextState(WinInteractState *sMachine, QHoverEvent *event, quint32 hint)
{
    return;
}

void DropProcess::nextState(WinInteractState *sMachine, QDropEvent *event, quint32)
{
    appWindow->removeLastDockable();
    rubberBand.reset();

    QQuickItem *item=new BasicDockItem();

    appWindow->addDockable(item);
    item->update();
    appWindow->arrangeDockables();

    dropWindow->destroy();

    sMachine->setIState(new IdleProcess);
}

void DropProcess::nextState(WinInteractState *sMachine, QDragLeaveEvent *event, quint32)
{
    appWindow->removeLastDockable();
    rubberBand.reset();
    appWindow->arrangeDockables();
    sMachine->setIState(new IdleProcess);
}
