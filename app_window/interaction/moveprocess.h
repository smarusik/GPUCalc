#ifndef MOVEPROCESS_H
#define MOVEPROCESS_H

#include "resizeready.h"

class MoveProcess:public ResizeReady
{
public:
    MoveProcess(quint32 hint, QQuickWindow *hW);

    virtual void trackMousePosition(const QPointF &pos) override;

    virtual bool updateRubberBand();

    virtual bool isInResizingState();

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32 hint) override;
protected:
    QQuickWindow *hostWindow;
    QRect originalPos;
    QPointF mouseOffset;
    QRect rbGeometry;
};

#endif // MOVEPROCESS_H
