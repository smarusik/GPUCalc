#include "resizeprocess.h"
#include "idleprocess.h"

ResizeProcess::ResizeProcess(quint32 hint, QQuickWindow *hW):
    ResizeReady(hint),
    hostWindow(hW)
{

    QRect newGeometry(hostWindow->screen()->virtualGeometry().topLeft(),
                      hostWindow->screen()->virtualGeometry().bottomRight());
    qDebug()<<newGeometry;
    QRect oldGeometry=hostWindow->geometry();
    qDebug()<<oldGeometry;

    if(direction&ResizeTop)
    {
        newGeometry.setLeft(oldGeometry.left());
        newGeometry.setRight(oldGeometry.right());
        newGeometry.setBottom(oldGeometry.bottom());
    }
    else if (direction&ResizeBottom) {
        newGeometry.setLeft(oldGeometry.left());
        newGeometry.setRight(oldGeometry.right());
        newGeometry.setTop(oldGeometry.top());
    }
    else if (direction&ResizeLeft) {
        newGeometry.setTop(oldGeometry.top());
        newGeometry.setBottom(oldGeometry.bottom());
        newGeometry.setRight(oldGeometry.right());
    }
    else if (direction&ResizeRight) {
        newGeometry.setTop(oldGeometry.top());
        newGeometry.setBottom(oldGeometry.bottom());
        newGeometry.setLeft(oldGeometry.left());
    }
    else if (direction&ResizeLeftTop) {
        newGeometry.setBottom(oldGeometry.bottom());
        newGeometry.setRight(oldGeometry.right());
    }
    else if (direction&ResizeRightTop) {
        newGeometry.setBottom(oldGeometry.bottom());
        newGeometry.setLeft(oldGeometry.left());
    }
    else if (direction&ResizeLeftBottom) {
        newGeometry.setTop(oldGeometry.top());
        newGeometry.setRight(oldGeometry.right());
    }
    else if (direction&ResizeRightBottom) {
        newGeometry.setTop(oldGeometry.top());
        newGeometry.setLeft(oldGeometry.left());
    }

    qDebug()<<newGeometry;
    hostWindow->setGeometry(newGeometry);

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

    QRect hwGeometry=hostWindow->geometry();

    if(direction&ResizeTop)
    {
        rbGeometry.setLeft(hwGeometry.left());
        rbGeometry.setRight(hwGeometry.right());
        rbGeometry.setBottom(hwGeometry.bottom());

        rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                              mousePosition.y():hwGeometry.bottom());
    }
    else if (direction&ResizeBottom)
    {
        rbGeometry.setLeft(hwGeometry.left());
        rbGeometry.setRight(hwGeometry.right());
        rbGeometry.setTop(hwGeometry.top());

        rbGeometry.setBottom(mousePosition.y()>hwGeometry.top()?
                                 mousePosition.y():hwGeometry.top());
    }
    else if (direction&ResizeLeft)
    {
        rbGeometry.setTop(hwGeometry.top());
        rbGeometry.setBottom(hwGeometry.bottom());
        rbGeometry.setRight(hwGeometry.right());

        rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                               mousePosition.x():hwGeometry.right());
    }
    else if (direction&ResizeRight)
    {
        rbGeometry.setTop(hwGeometry.top());
        rbGeometry.setBottom(hwGeometry.bottom());
        rbGeometry.setLeft(hwGeometry.left());

        rbGeometry.setRight(mousePosition.x()>hwGeometry.left()?
                                mousePosition.x():hwGeometry.left());
    }
    else if (direction&ResizeLeftTop)
    {
        rbGeometry.setBottom(hwGeometry.bottom());
        rbGeometry.setRight(hwGeometry.right());

        rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                               mousePosition.x():hwGeometry.right());
        rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                              mousePosition.y():hwGeometry.bottom());
    }
    else if (direction&ResizeRightTop)
    {
        rbGeometry.setBottom(hwGeometry.bottom());
        rbGeometry.setLeft(hwGeometry.left());

        rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                              mousePosition.y():hwGeometry.top());
        rbGeometry.setRight(mousePosition.x()>hwGeometry.left()?
                                mousePosition.x():hwGeometry.left());
    }
    else if (direction&ResizeLeftBottom)
    {
        rbGeometry.setTop(hwGeometry.top());
        rbGeometry.setRight(hwGeometry.right());

        rbGeometry.setBottom(mousePosition.y()>hwGeometry.top()?
                                 mousePosition.y():hwGeometry.top());
        rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                               mousePosition.x():hwGeometry.right());

    }
    else if (direction&ResizeRightBottom)
    {
        rbGeometry.setTop(hwGeometry.top());
        rbGeometry.setLeft(hwGeometry.left());

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
