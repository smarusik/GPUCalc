#ifndef RESIZECONFIRMATON_H
#define RESIZECONFIRMATON_H

#include "resizeready.h"

class BaseConfirmation : public ResizeReady
{
public:
    BaseConfirmation(quint32 hint, const QPoint &chkPt);
    virtual ~BaseConfirmation()
    {}

    virtual bool checkPositionDelta(const QPoint &pos) override;
private:
    QPoint confirmCheckPoint;
};


class ResizeConfirmaton : public BaseConfirmation
{
public:
    ResizeConfirmaton(quint32 hint, const QPoint &chkPt);
    virtual ~ResizeConfirmaton()
    {}

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event, quint32) override;
};

class MoveConfirmation : public BaseConfirmation
{
public:
    MoveConfirmation(const QPoint &chkPt);
    virtual ~MoveConfirmation()
    {}

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32) override;
};

class DragConfirmation : public BaseConfirmation
{
public:
    DragConfirmation(const QPoint &chkPt);
    virtual ~DragConfirmation()
    {}

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32) override;
};

#endif // RESIZECONFIRMATON_H
