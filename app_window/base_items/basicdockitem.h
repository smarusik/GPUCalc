#ifndef BASICDOCKITEM_H
#define BASICDOCKITEM_H

#include "backgrounditem.h"
#include "item_impl/borderitem.h"
#include "item_impl/titlebaritem.h"
#include "item_impl/statusbaritem.h"
#include <QQuickItem>
#include <QPointer>

class BasicDockItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(TitleBarItem* titleBar READ getTitleBar
               WRITE setTitleBar NOTIFY titleBarChanged)
    Q_PROPERTY(StatusBarItem* statusBar READ getStatusBar
               WRITE setStatusBar NOTIFY statusBarChanged)
public:
    BasicDockItem(QQuickItem *parent=nullptr);
    virtual ~BasicDockItem()
    {}

    TitleBarItem *getTitleBar() const;
    void setTitleBar(TitleBarItem *value);

    StatusBarItem *getStatusBar() const;
    void setStatusBar(StatusBarItem *value);

signals:
    void titleBarChanged(TitleBarItem *tBar);
    void statusBarChanged(TitleBarItem *sBar);

protected:
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    void setDefaults();
    void resizeInternals(const QSizeF &bgSize);
    void moveInternals(const QPointF &bgOrigin);

    QPointer<TitleBarItem> titleBar;
    QPointer<StatusBarItem> statusBar;
    BackgroundItem *background,*workingArea;

    quint16 frameWidth;
    quint16 titleBarHeight, statusBarHeight;
};

#endif // BASICDOCKITEM_H
