#ifndef WINDOWSTATES_H
#define WINDOWSTATES_H

#include "rubberband.h"
#include <QQuickWindow>
#include <QCursor>
#include <QObject>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QMutexLocker>

//States context
class BasicInteractState;

class WinInteractState : public QObject
{
    Q_OBJECT
    friend class ResizeReady;
    friend class ResizeProcess;
    friend class OrdinaryState;
public:
    explicit WinInteractState(QQuickWindow *parent);

    bool rearrangeSubwindows();
    QCursor getCursor();
    bool isInResizingState();
    bool trackMousePosition(const QPointF &pos);
    const QRect &getStartGeometry();
    bool updateRubberBand();

    void nextIState(QMouseEvent *event, quint32 hint=0);
    void nextIState(QHoverEvent *event, quint32 hint=0);

    void setIState(BasicInteractState *value);

    QPointF getMousePosition() const;

    void setStartGeometry(const QRect &value);

private:
    QScopedPointer<BasicInteractState> iState;
    QQuickWindow *parentWindow;
    QPointF mousePosition, stableCorner;
    QRect startGeometry;
};



//Interactive state IF
class BasicInteractState
{
public:
    BasicInteractState()
    {}

    enum StateHint
    {
        ResizeTop=1,
        ResizeBottom=2,
        ResizeLeft=4,
        ResizeRight=8,

        ResizeHorizontal=ResizeLeft|ResizeRight,
        ResizeVertical=ResizeBottom|ResizeTop,
        ResizeRightTop=16,
        ResizeLeftTop=32,
        ResizeRightBottom=64,
        ResizeLeftBottom=128,

        ResizeDiagRight=ResizeLeftTop|ResizeRightBottom,/* \ */
        ResizeDiagLeft=ResizeRightTop|ResizeLeftBottom, /* / */

        ResizeGen=ResizeHorizontal
                |ResizeVertical
                |ResizeDiagLeft
                |ResizeDiagRight

    };

    enum ResizeOrigin
    {
        FromTop=1,
        FromBottom=2,
        FromLeft=4,
        FromRight=8
    };

    virtual bool rearrangeSubwindows()
    {
        return false;
    }


    virtual QCursor getCursor()
    {
        return cursor;
    }

    virtual bool updateRubberBand()
    {
        return false;
    }

    virtual bool isInResizingState()
    {
        return false;
    }

    virtual bool needFixResize()
    {
        return false;
    }

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32 hint=0)=0;

    virtual void nextState(WinInteractState *sMachine,
                                          QHoverEvent *event,
                                          quint32 hint=0)=0;
    QPointF getMousePosition() const;

protected:
    QCursor cursor;
    quint32 direction;
};

//Particular states of interaction

class ResizeReady: public BasicInteractState
{
public:
    ResizeReady(quint32 hint)
    {
        direction=hint;

        if(direction&ResizeHorizontal)
            cursor=Qt::SizeHorCursor;
        else if(direction&ResizeVertical)
            cursor=Qt::SizeVerCursor;
        else if(direction&ResizeDiagLeft)
            cursor=Qt::SizeBDiagCursor;
        else if(direction&ResizeDiagRight)
            cursor=Qt::SizeFDiagCursor;
        else
            cursor=Qt::ArrowCursor;
    }

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32 hint) override;

    virtual void nextState(WinInteractState *sMachine,
                                          QHoverEvent *event,
                                          quint32 hint) override;

};

class ResizeProcess:public ResizeReady
{
public:
    ResizeProcess(quint32 hint):
        ResizeReady(hint)
    {
    }

    virtual bool updateRubberBand()
    {
        return true;
    }

    virtual bool isInResizingState()
    {
        return true;
    }

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32 hint) override;
};

class OrdinaryState:public BasicInteractState
{
public:
    OrdinaryState()
    {
        cursor=QCursor(Qt::ArrowCursor);
    }

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32 hint=0) override;

    virtual void nextState(WinInteractState *sMachine,
                                          QHoverEvent *event,
                                          quint32 hint=0) override;
};

#endif // WINDOWSTATES_H
