#ifndef ITEMWINDOW_H
#define ITEMWINDOW_H

#include "windowstates.h"
#include "backgrounditem.h"
#include "contentlessitems.h"
#include <QQuickWindow>
#include <QPointer>

class BasicWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* titleBar READ getTitleBar WRITE setTitleBar NOTIFY titleBarChanged)
    Q_PROPERTY(BaseContentlessItem* workingArea READ getWorkingArea WRITE setWorkingArea)
public:
    BasicWindow(QWindow *parent=nullptr);
    virtual ~BasicWindow()
    {}

    // QWindow interface
    QQuickItem *getTitleBar() const;
    void setTitleBar(QQuickItem *value);

    BaseContentlessItem *getWorkingArea() const;
    void setWorkingArea(BaseContentlessItem *value);

signals:
    void titleBarChanged(QQuickItem *titleBar);

private:
    virtual void timerEvent(QTimerEvent *);

    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void moveEvent(QMoveEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual bool event(QEvent *event) override;

    void setDefaults();
    void resizeInternals(const QSize &backgroundSize);

    QQuickItem *titleBar;
    BaseContentlessItem *workingArea;
    BorderItem *lBorder,*rBorder,*tBorder,*bBorder,
                        *lbCorner,*rbCorner,*ltCorner,*rtCorner;
    BackgroundItem *background;
    QScopedPointer<RubberBandItem, QScopedPointerDeleteLater> rubberBand;

    WinInteractState interState;

    quint16 frameWidth;
    quint16 titleBarHeight;
};



#endif // ITEMWINDOW_H
