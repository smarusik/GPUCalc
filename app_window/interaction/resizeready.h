#ifndef RESIZEREADY_H
#define RESIZEREADY_H

#include "wininteractstate.h"

class ResizeReady: public BasicInteractState
{
public:
    ResizeReady(quint32 hint);
    virtual ~ResizeReady()
    {}

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event, quint32) override;

    virtual void nextState(WinInteractState *sMachine,
                                          QHoverEvent *event,
                                          quint32 hint) override;
};

#endif // RESIZEREADY_H
