#ifndef DOCKINGPLACEITEM_H
#define DOCKINGPLACEITEM_H

#include "base_items/basiccontentlessitem.h"

class DockingPlaceItem : public BasicContentlessItem
{
public:
    DockingPlaceItem(QQuickItem *parent=nullptr);

private:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;

};

#endif // DOCKINGPLACEITEM_H
