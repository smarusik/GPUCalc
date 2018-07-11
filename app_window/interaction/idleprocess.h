#ifndef IDLINGSTATE_H
#define IDLINGSTATE_H

#include "wininteractstate.h"

class IdleProcess:public BasicInteractState
{
public:
    IdleProcess();

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32 hint=0) override;

    virtual void nextState(WinInteractState *sMachine,
                                          QHoverEvent *event,
                                          quint32 hint=0) override;
};

#endif // IDLINGSTATE_H
