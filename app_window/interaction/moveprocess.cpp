#include "moveprocess.h"
#include "idleprocess.h"

MoveProcess::MoveProcess(quint32 hint, QQuickWindow *hW):
    ResizeReady(hint),
    hostWindow(hW)
{
    cursor=Qt::ClosedHandCursor;

    originalPos=hostWindow->geometry();
    hostWindow->setGeometry(hostWindow->screen()->virtualGeometry());
    rubberBand.reset(new RubberBandItem(hostWindow->contentItem()));
}

void MoveProcess::trackMousePosition(const QPointF &pos)
{
    mousePosition=pos;
    if(mouseOffset.isNull())
    {
        mouseOffset=mousePosition-originalPos.topLeft();
    }
}

bool MoveProcess::updateRubberBand()
{
    if(!rubberBand)
    {
        return false;
    }

    QRect hwGeometry=hostWindow->geometry();

    QPointF adjustedMPos(mousePosition.x()-mouseOffset.x(),mousePosition.y()-mouseOffset.y());

    if (direction&Move)
    {
        if(adjustedMPos.y()<=hwGeometry.top())
        {
            rbGeometry.setTop(hwGeometry.top());
        }
        else if(adjustedMPos.y()>=hwGeometry.bottom()-originalPos.height())
        {
            rbGeometry.setTop(hwGeometry.bottom()-originalPos.height());
        }
        else
        {
            rbGeometry.setTop(adjustedMPos.y());
        }

        if(adjustedMPos.x()<=hwGeometry.left())
        {
            rbGeometry.setLeft(hwGeometry.left());
        }
        else if(adjustedMPos.x()>=hwGeometry.right()-originalPos.width())
        {
            rbGeometry.setLeft(hwGeometry.right()-originalPos.width());
        }
        else
        {
            rbGeometry.setLeft(adjustedMPos.x());
        }

        rbGeometry.setSize(originalPos.size());
    }

    rubberBand->setBounds(QRect(hostWindow->contentItem()->mapFromGlobal(rbGeometry.topLeft()).toPoint(),
                                rbGeometry.size()));

    return true;
}

bool MoveProcess::isInResizingState()
{
    return true;
}

void MoveProcess::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
    if(event->type()&QEvent::MouseButtonRelease
            && event->button()&Qt::LeftButton)
    {
        QRect newWindowGeometry(rbGeometry);
        sMachine->setIState(new IdleProcess);
        sMachine->parentWindow->setGeometry(newWindowGeometry);
    }
}
