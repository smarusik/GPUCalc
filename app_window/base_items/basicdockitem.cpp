#include "basicdockitem.h"

BasicDockItem::BasicDockItem(QQuickItem *parent):
    QQuickItem(parent)
{
    setDefaults();

    background=new BackgroundItem;
    background->setParentItem(this);
    background->setPosition(QPointF(0,0));
    background->setColor(Qt::gray);

    workingArea=new BackgroundItem(background);
    workingArea->setColor(Qt::white);
}

QSGNode *BasicDockItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    if(oldNode)
    {
        return oldNode;
    }
    else
    {
        return new QSGNode;
    }
}

void BasicDockItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    resizeInternals(newGeometry.size());
    moveInternals(newGeometry.topLeft());
}

void BasicDockItem::setDefaults()
{
    frameWidth=5;
    titleBarHeight=20;
    statusBarHeight=20;
}

void BasicDockItem::resizeInternals(const QSizeF &bgSize)
{
    background->setSize(bgSize);
    workingArea->setSize(background->size()-2*QSizeF(frameWidth,frameWidth));

    if(titleBar)
    {
        titleBar->setSize(QSizeF(background->width()-2*frameWidth,titleBarHeight));
        workingArea->setHeight(workingArea->height()-titleBarHeight);
    }

    if(statusBar)
    {
        statusBar->setSize(QSizeF(background->width()-2*frameWidth,statusBarHeight));
        workingArea->setHeight(workingArea->height()-statusBarHeight);
    }
}

void BasicDockItem::moveInternals(const QPointF &bgOrigin)
{
    background->setPosition(bgOrigin);
    workingArea->setPosition(QPointF(frameWidth,frameWidth));

    if(titleBar)
    {
        titleBar->setPosition(QPointF(frameWidth,frameWidth));
        workingArea->setPosition(workingArea->position()+QPointF(0,titleBarHeight));
    }

    if(statusBar)
    {
        statusBar->setPosition(QPointF(frameWidth,background->height()-frameWidth-statusBar->height()));
    }
}

StatusBarItem *BasicDockItem::getStatusBar() const
{
    return statusBar;
}

void BasicDockItem::setStatusBar(StatusBarItem *value)
{
    statusBar = value;
    statusBar->setParentItem(background);
}

TitleBarItem *BasicDockItem::getTitleBar() const
{
    return titleBar;
}

void BasicDockItem::setTitleBar(TitleBarItem *value)
{
    titleBar = value;
    titleBar->setParentItem(background);
}
