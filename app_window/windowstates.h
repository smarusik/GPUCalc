#ifndef WINDOWSTATES_H
#define WINDOWSTATES_H

#include "rubberband.h"
#include <QQuickWindow>
#include <QScreen>
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
    void trackMousePosition(const QPointF &pos);
    const QRect &getStartGeometry();
    bool updateRubberBand();

    void nextIState(QMouseEvent *event, quint32 hint=0);
    void nextIState(QHoverEvent *event, quint32 hint=0);

    void setIState(BasicInteractState *value);
    void setStartGeometry(const QRect &value);

private:
    QScopedPointer<BasicInteractState> iState;
    QQuickWindow *parentWindow;
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
protected:
    QCursor cursor;
    quint32 direction;
    QPointF mousePosition;
    QScopedPointer<RubberBandItem, QScopedPointerDeleteLater> rubberBand;
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
    ResizeProcess(quint32 hint, QQuickWindow *hW):
        ResizeReady(hint),
        hostWindow(hW)
    {

        QRect newGeometry(hostWindow->screen()->availableGeometry().topLeft(),
                          hostWindow->screen()->availableGeometry().bottomRight());
        QRect oldGeometry=hostWindow->geometry();

        if(direction&ResizeTop)
        {
            newGeometry.setLeft(oldGeometry.left());
            newGeometry.setRight(oldGeometry.right());
            newGeometry.setBottom(oldGeometry.bottom());
        }
        else if (direction&ResizeBottom) {
            newGeometry.setLeft(oldGeometry.left());
            newGeometry.setRight(oldGeometry.right());
            newGeometry.setTop(oldGeometry.top());
        }
        else if (direction&ResizeLeft) {
            newGeometry.setTop(oldGeometry.top());
            newGeometry.setBottom(oldGeometry.bottom());
            newGeometry.setRight(oldGeometry.right());
        }
        else if (direction&ResizeRight) {
            newGeometry.setTop(oldGeometry.top());
            newGeometry.setBottom(oldGeometry.bottom());
            newGeometry.setLeft(oldGeometry.left());
        }
        else if (direction&ResizeLeftTop) {
            newGeometry.setBottom(oldGeometry.bottom());
            newGeometry.setRight(oldGeometry.right());
        }
        else if (direction&ResizeRightTop) {
            newGeometry.setBottom(oldGeometry.bottom());
            newGeometry.setLeft(oldGeometry.left());
        }
        else if (direction&ResizeLeftBottom) {
            newGeometry.setTop(oldGeometry.top());
            newGeometry.setRight(oldGeometry.right());
        }
        else if (direction&ResizeRightBottom) {
            newGeometry.setTop(oldGeometry.top());
            newGeometry.setLeft(oldGeometry.left());
        }

        hostWindow->setGeometry(newGeometry);
        rubberBand.reset(new RubberBandItem(hostWindow->contentItem()));
    }

    virtual void trackMousePosition(const QPointF &pos) override
    {
        mousePosition=pos;
    }

    virtual bool updateRubberBand()
    {
        if(!rubberBand)
        {
            return false;
        }

        QRect hwGeometry=hostWindow->geometry();

        if(direction&ResizeTop)
        {
            rbGeometry.setLeft(hwGeometry.left());
            rbGeometry.setRight(hwGeometry.right());
            rbGeometry.setBottom(hwGeometry.bottom());

            rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                                  mousePosition.y():hwGeometry.bottom());
        }
        else if (direction&ResizeBottom) {
            rbGeometry.setLeft(hwGeometry.left());
            rbGeometry.setRight(hwGeometry.right());
            rbGeometry.setTop(hwGeometry.top());

            rbGeometry.setBottom(mousePosition.y()>hwGeometry.top()?
                                  mousePosition.y():hwGeometry.top());
        }
        else if (direction&ResizeLeft) {
            rbGeometry.setTop(hwGeometry.top());
            rbGeometry.setBottom(hwGeometry.bottom());
            rbGeometry.setRight(hwGeometry.right());

            rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                                  mousePosition.x():hwGeometry.right());
        }
        else if (direction&ResizeRight) {
            rbGeometry.setTop(hwGeometry.top());
            rbGeometry.setBottom(hwGeometry.bottom());
            rbGeometry.setLeft(hwGeometry.left());

            rbGeometry.setRight(mousePosition.x()>hwGeometry.left()?
                                  mousePosition.x():hwGeometry.left());
        }
        else if (direction&ResizeLeftTop) {
            rbGeometry.setBottom(hwGeometry.bottom());
            rbGeometry.setRight(hwGeometry.right());

            rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                                  mousePosition.x():hwGeometry.right());
            rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                                  mousePosition.y():hwGeometry.bottom());
        }
        else if (direction&ResizeRightTop) {
            rbGeometry.setBottom(hwGeometry.bottom());
            rbGeometry.setLeft(hwGeometry.left());

            rbGeometry.setTop(mousePosition.y()<hwGeometry.bottom()?
                                  mousePosition.y():hwGeometry.top());
            rbGeometry.setRight(mousePosition.x()>hwGeometry.left()?
                                  mousePosition.x():hwGeometry.left());
        }
        else if (direction&ResizeLeftBottom) {
            rbGeometry.setTop(hwGeometry.top());
            rbGeometry.setRight(hwGeometry.right());

            rbGeometry.setBottom(mousePosition.y()>hwGeometry.top()?
                                  mousePosition.y():hwGeometry.top());
            rbGeometry.setLeft(mousePosition.x()<hwGeometry.right()?
                                  mousePosition.x():hwGeometry.right());

        }
        else if (direction&ResizeRightBottom) {
            rbGeometry.setTop(hwGeometry.top());
            rbGeometry.setLeft(hwGeometry.left());

            rbGeometry.setBottom(mousePosition.y()>hwGeometry.top()?
                                  mousePosition.y():hwGeometry.top());
            rbGeometry.setRight(mousePosition.x()>hwGeometry.left()?
                                  mousePosition.x():hwGeometry.left());
        }

        rubberBand->setBounds(QRect(hostWindow->contentItem()->mapFromGlobal(rbGeometry.topLeft()).toPoint(),
                                    rbGeometry.size()));

        return true;
    }

    virtual bool isInResizingState()
    {
        return true;
    }

    virtual void nextState(WinInteractState *sMachine,
                                          QMouseEvent *event,
                                          quint32 hint) override;
private:
    QQuickWindow *hostWindow;
    QRect rbGeometry;
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
