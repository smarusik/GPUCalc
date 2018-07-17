#include "dockingplaceitem.h"
#include "window_impl/channelwindow.h"

DockingPlaceItem::DockingPlaceItem(QQuickItem *parent):
    BasicContentlessItem(parent)
{
    setFlag(QQuickItem::ItemAcceptsDrops);
}

void DockingPlaceItem::dragEnterEvent(QDragEnterEvent *event)
{
    ChannelWindow *dropableWindow=qobject_cast<ChannelWindow *>(event->source());

    if(dropableWindow)
    {
        event->acceptProposedAction();
        interState->nextIState(event);
    }
}

void DockingPlaceItem::dragMoveEvent(QDragMoveEvent *event)
{
    interState->trackMousePosition(event->pos());
}

void DockingPlaceItem::dragLeaveEvent(QDragLeaveEvent *event)
{
    interState->nextIState(event);
}

void DockingPlaceItem::dropEvent(QDropEvent *event)
{
    interState->nextIState(event);
}
