#ifndef VNAAPPWINDOW_H
#define VNAAPPWINDOW_H

#include "base_windows/basicwindow.h"
#include "base_items/basicdockitem.h"
#include "item_impl/dockingplaceitem.h"
#include <QObject>
#include <QList>

class VNAAppWindow : public BasicWindow
{
    Q_OBJECT
public:
    VNAAppWindow(QWindow *parent=nullptr);

    virtual ~VNAAppWindow()
    {}

    void addDockable(QQuickItem* dock);
    bool removeLastDockable();
    bool arrangeDockables();


    DockingPlaceItem *getDockArea() const;

private:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    QList<QQuickItem*> dockables;
    DockingPlaceItem *dockArea;

};



#endif // VNAAPPWINDOW_H
