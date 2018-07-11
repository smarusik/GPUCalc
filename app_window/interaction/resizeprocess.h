#ifndef RESIZEPROCESS_H
#define RESIZEPROCESS_H

#include "resizeready.h"

class ResizeProcess:public ResizeReady
{
public:
    ResizeProcess(quint32 hint, QQuickWindow *hW);

    virtual void trackMousePosition(const QPointF &pos) override;

    virtual bool updateRubberBand() override;

    virtual bool isInResizingState() override;

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32 hint) override;
private:
    QQuickWindow *hostWindow;
    QRect rbGeometry;
    QRect hwGeometry;
};

#endif // RESIZEPROCESS_H
