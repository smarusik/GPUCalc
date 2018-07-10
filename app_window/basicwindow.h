#ifndef ITEMWINDOW_H
#define ITEMWINDOW_H

#include "windowstates.h"
#include "backgrounditem.h"
#include "contentlessitems.h"
#include "titlebaritem.h"
#include <QQuickWindow>
#include <QPointer>

class BasicWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* titleBarContent READ getTitleBarContent
               WRITE setTitleBarContent NOTIFY titleBarContentChanged)
    Q_PROPERTY(BaseContentlessItem* workingArea READ getWorkingArea WRITE setWorkingArea)
public:
    BasicWindow(QWindow *parent=nullptr);
    virtual ~BasicWindow()
    {}

    // QWindow interface
    QQuickItem *getTitleBarContent() const;
    void setTitleBarContent(QQuickItem *value);

    BaseContentlessItem *getWorkingArea() const;
    void setWorkingArea(BaseContentlessItem *value);

signals:
    void titleBarContentChanged(QQuickItem *titleBarContent);

private:
    virtual void timerEvent(QTimerEvent *);

    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void moveEvent(QMoveEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual bool event(QEvent *event) override;

    void setDefaults();
    void resizeInternals(const QSize &bgSize);
    void moveInternals(const QPoint &bgOrigin);

    TitleBarItem *titleBar;
    QQuickItem *titleBarContent;
    BaseContentlessItem *workingArea;
    BorderItem *lBorder,*rBorder,*tBorder,*bBorder,
                        *lbCorner,*rbCorner,*ltCorner,*rtCorner;
    BackgroundItem *background;

    WinInteractState interState;

    quint16 frameWidth;
    quint16 titleBarHeight;
};



#endif // ITEMWINDOW_H
