#ifndef RESIZECONFIRMATON_H
#define RESIZECONFIRMATON_H

#include "resizeready.h"

class BaseConfirmaton : public ResizeReady
{
public:
    BaseConfirmaton(quint32 hint, const QPoint &chkPt);
    virtual ~BaseConfirmaton()
    {}

    virtual bool checkPositionDelta(const QPoint &pos) override;
private:
    QPoint resizeCheckPoint;
};


class ResizeConfirmaton : public BaseConfirmaton
{
public:
    ResizeConfirmaton(quint32 hint, const QPoint &chkPt);
    virtual ~ResizeConfirmaton()
    {}

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event, quint32) override;
private:
    QPoint resizeCheckPoint;
};

class MoveConfirmaton : public BaseConfirmaton
{
public:
    MoveConfirmaton(const QPoint &chkPt);
    virtual ~MoveConfirmaton()
    {}

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32) override;
private:
    QPoint resizeCheckPoint;
};

#endif // RESIZECONFIRMATON_H
