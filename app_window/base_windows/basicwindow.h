#ifndef ITEMWINDOW_H
#define ITEMWINDOW_H

#include "interaction/wininteractstate.h"
#include "backgrounditem.h"
#include "item_impl/borderitem.h"
#include "item_impl/titlebaritem.h"
#include "item_impl/statusbaritem.h"
#include <QQuickWindow>
#include <QPointer>

class BasicWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(TitleBarItem* titleBar READ getTitleBar
               WRITE setTitleBar NOTIFY titleBarChanged)
    Q_PROPERTY(StatusBarItem* statusBar READ getStatusBar
               WRITE setStatusBar NOTIFY statusBarChanged)
public:
    BasicWindow(QWindow *parent=nullptr);
    virtual ~BasicWindow()
    {}

    TitleBarItem *getTitleBar() const;
    void setTitleBar(TitleBarItem *value);

    StatusBarItem *getStatusBar() const;
    void setStatusBar(StatusBarItem *value);

    WinInteractState &getInterState();

signals:
    void titleBarChanged(TitleBarItem *tBar);
    void statusBarChanged(TitleBarItem *sBar);

protected:
    virtual void timerEvent(QTimerEvent *) override;

    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void moveEvent(QMoveEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual bool event(QEvent *event) override;

    void setDefaults();
    void resizeInternals(const QSize &bgSize);
    void moveInternals(const QPoint &bgOrigin);

    QPointer<TitleBarItem> titleBar;
    QPointer<StatusBarItem> statusBar;
    BasicContentlessItem *workingArea;
    BorderItem *lBorder,*rBorder,*tBorder,*bBorder,
                        *lbCorner,*rbCorner,*ltCorner,*rtCorner;
    BackgroundItem *background;

    WinInteractState interState;

    quint16 frameWidth;
    quint16 titleBarHeight, statusBarHeight;
};



#endif // ITEMWINDOW_H
