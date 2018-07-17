#ifndef DROPPROCESS_H
#define DROPPROCESS_H

class VNAAppWindow;
class BasicWindow;

#include "wininteractstate.h"

class DropProcess : public BasicInteractState
{
public:
    DropProcess(VNAAppWindow *bW, BasicWindow *dW);

    virtual void trackMousePosition(const QPointF &) override;

    virtual bool updateRubberBand()override;

    virtual bool isInResizingState()override;

    virtual void nextState(WinInteractState *sMachine,
                           QMouseEvent *event,
                           quint32 hint) override;

    virtual void nextState(WinInteractState *sMachine,
                           QHoverEvent *event,
                           quint32 hint) override;

    virtual void nextState(WinInteractState *sMachine, QDropEvent *event, quint32 ) override;
    virtual void nextState(WinInteractState *sMachine, QDragLeaveEvent *event, quint32) override;

private:
    VNAAppWindow *appWindow;
    BasicWindow *dropWindow;
    QRect originalPos;
    QRect rbGeometry;
};

#endif // DROPPROCESS_H
