#include "dragprocess.h"

DragProcess::DragProcess(quint32 hint, QQuickWindow *hW):
    MoveProcess(BasicInteractState::Drag,hW)
{
    cursor=Qt::DragMoveCursor;
}

//bool DragProcess::updateRubberBand()
//{

//}
