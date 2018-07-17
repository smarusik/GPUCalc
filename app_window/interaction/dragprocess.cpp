#include "window_impl/vnaappwindow.h"
#include "dragprocess.h"
#include <QDrag>
#include <QMimeData>
#include "idleprocess.h"


DragProcess::DragProcess(quint32 hint, BasicWindow *hW):
    ResizeReady(BasicInteractState::Drag),
    hostWindow(hW)
{
    QDrag *drag = new QDrag(hostWindow);

    QMimeData *mimeData = new QMimeData;
    mimeData->setText("Freaking window data!");
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
}

void DragProcess::trackMousePosition(const QPointF &pos)
{
    return;
}

bool DragProcess::updateRubberBand()
{
    return false;
}

bool DragProcess::isInResizingState()
{
    return false;
}

void DragProcess::nextState(WinInteractState *sMachine, QMouseEvent *event, quint32 hint)
{
        sMachine->setIState(new IdleProcess);
}
