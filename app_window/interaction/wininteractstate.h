#ifndef WINDOWSTATES_H
#define WINDOWSTATES_H

#include "rubberband.h"
#include <QScreen>
#include <QCursor>
#include <QObject>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QMutexLocker>
#include <QGuiApplication>

//States context
class BasicInteractState;
class BasicWindow;

class WinInteractState : public QObject
{
    Q_OBJECT
    friend class IdleProcess;
    friend class ResizeReady;
    friend class ResizeConfirmaton;
    friend class MoveConfirmation;
    friend class DragConfirmation;
    friend class ResizeProcess;
    friend class MoveProcess;
    friend class DragProcess;
    friend class DropProcess;
    friend class OrdinaryState;
public:
    explicit WinInteractState(BasicWindow *parent);

    QCursor getCursor();
    bool isInResizingState();
    bool checkPositionDelta(const QPoint &pos);
    void trackMousePosition(const QPointF &pos);
    const QRect &getStartGeometry();
    bool updateRubberBand();

    void nextIState(QMouseEvent *event, quint32 hint=0);
    void nextIState(QHoverEvent *event, quint32 hint=0);
    void nextIState(QDragEnterEvent *event, quint32 hint=0);
    void nextIState(QDragLeaveEvent *event, quint32 hint=0);
    void nextIState(QDropEvent *event, quint32 hint=0);

    void setIState(BasicInteractState *value);
    void setStartGeometry(const QRect &value);

private:
    QScopedPointer<BasicInteractState> iState;
    BasicWindow *parentWindow;
    QRect startGeometry;
};

//Interactive state IF
class BasicInteractState
{
public:
    BasicInteractState()
    {}

    virtual ~BasicInteractState()
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

        ResizeGeneral=ResizeHorizontal
                |ResizeVertical
                |ResizeDiagLeft
                |ResizeDiagRight,

        Move=256,
        Drag=512
    };

    enum ResizeOrigin
    {
        FromTop=1,
        FromBottom=2,
        FromLeft=4,
        FromRight=8
    };

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

    virtual bool checkPositionDelta(const QPoint &pos)
    {
        return false;
    }

    virtual void trackMousePosition(const QPointF &)
    {
        return;
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

    virtual void nextState(WinInteractState *sMachine,
                                          QDragEnterEvent *event,
                                          quint32 hint=0)
    {}

    virtual void nextState(WinInteractState *sMachine,
                                          QDragLeaveEvent *event,
                                          quint32 hint=0)
    {}

    virtual void nextState(WinInteractState *sMachine,
                                          QDropEvent *event,
                                          quint32 hint=0)
    {}

protected:
    QCursor cursor;
    quint32 direction;
    QPointF mousePosition;
    QScopedPointer<RubberBandItem, QScopedPointerDeleteLater> rubberBand;
};

#endif // WINDOWSTATES_H
