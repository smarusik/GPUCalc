#include "resizeprocess.h"
#include "idleprocess.h"

ResizeProcess::ResizeProcess(quint32 hint, QQuickWindow *hW):
    ResizeReady(hint),
    hostWindow(hW)
{
    hwGeometry=hostWindow->geometry();
    hostWindow->setGeometry(hostWindow->screen()->availableVirtualGeometry());
    rubberBand.reset(new RubberBandItem(hostWindow->contentItem()));
}

void ResizeProcess::trackMousePosition(const QPointF &pos)
{
    mousePosition=pos;
}

bool ResizeProcess::updateRubberBand()
{
    if(!rubberBand)
    {
        return false;
    }

    rbGeometry=hwGeometry;

    if(direction&ResizeTop)
    {
        rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                              mousePosition.y():hwGeometry.bottom());
    }
    else if (direction&ResizeBottom)
    {
        rbGeometry.setBottom(mousePosition.y()>hwGeometry.top()?
                                 mousePosition.y():hwGeometry.top());
    }
    else if (direction&ResizeLeft)
    {
        rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                               mousePosition.x():hwGeometry.right());
    }
    else if (direction&ResizeRight)
    {
        rbGeometry.setRight(mousePosition.x()>hwGeometry.left()?
                                mousePosition.x():hwGeometry.left());
    }
    else if (direction&ResizeLeftTop)
    {
        rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                               mousePosition.x():hwGeometry.right());
        rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                              mousePosition.y():hwGeometry.bottom());
    }
    else if (direction&ResizeRightTop)
    {
        rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                              mousePosition.y():hwGeometry.top());
        rbGeometry.setRight(mousePosition.x()>hwGeometry.left()?
                                mousePosition.x():hwGeometry.left());
    }
    else if (direction&ResizeLeftBottom)
    {
        rbGeometry.setBottom(mousePosition.y()>hwGeometry.top()?
                                 mousePosition.y():hwGeometry.top());
        rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                               mousePosition.x():hwGeometry.right());

    }
    else if (direction&ResizeRightBottom)
    {
        rbGeometry.setBottom(mousePosition.y()>hwGeometry.top()?
                                 mousePosition.y():hwGeometry.top());
        rbGeometry.setRight(mousePosition.x()>hwGeometry.left()?
                                mousePosition.x():hwGeometry.left());
    }

    rubberBand->setBounds(QRect(hostWindow->contentItem()->mapFromGlobal(rbGeometry.topLeft()).toPoint(),
                                rbGeometry.size()));

    return true;
}

bool ResizeProcess::isInResizingState()
{
    return true;
}

void ResizeProcess::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
    if(event->type()&QEvent::MouseButtonRelease
            && event->button()&Qt::LeftButton)
    {
        QRect newWindowGeometry(rbGeometry);
        sMachine->setIState(new IdleProcess);
        sMachine->parentWindow->setGeometry(newWindowGeometry);
    }
}
