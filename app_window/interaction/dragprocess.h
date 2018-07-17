#ifndef DRAGPROCESS_H
#define DRAGPROCESS_H

#include "moveprocess.h"

class VNAAppWindow;
class BasicWindow;

class DragProcess : public ResizeReady
{
public:
    DragProcess(quint32 hint, BasicWindow *hW);
    virtual void trackMousePosition(const QPointF &pos) override;

    virtual bool updateRubberBand()override;

    virtual bool isInResizingState()override;

    virtual void nextState(WinInteractState *sMachine,
                           QMouseEvent *event,
                           quint32 hint) override;
protected:
    BasicWindow *hostWindow;
};

#endif // DRAGPROCESS_H
