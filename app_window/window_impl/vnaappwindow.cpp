#include "vnaappwindow.h"
#include "channelwindow.h"
#include <math.h>
#include <stdlib.h>


VNAAppWindow::VNAAppWindow(QWindow *parent):
    BasicWindow(parent)
{

    for(int i=0; i<7; i++)
    {
        BasicDockItem *item=new BasicDockItem(workingArea);

        dockables.push_back(item);
        item->update();
    }

    dockArea=new DockingPlaceItem(workingArea);
    dockArea->setInterState(&interState);
}

void VNAAppWindow::addDockable(QQuickItem *dock)
{
    dock->setParentItem(workingArea);
    dockables.push_back(dock);
}

bool VNAAppWindow::removeLastDockable()
{
    dockables.removeLast();
}

bool VNAAppWindow::arrangeDockables()
{
    if(dockables.count()==0)
    {
        return false;
    }

    qreal dockablesNum=dockables.size();
    qreal ratio=workingArea->width()/workingArea->height();

    if(ratio<=0)
    {
        return false;
    }

    qreal rCols=std::sqrt(dockablesNum*ratio);
    int cols=rCols>=dockablesNum?dockablesNum:std::ceil(rCols);
    std::div_t distr=std::div(dockablesNum,cols);
    int raws=distr.quot + (distr.rem>0?1:0);
    qreal vStep=workingArea->height()/raws;
    qreal hStep=workingArea->width()/cols;

    int curCol=cols;

    for(int i=0; i<raws; ++i)
    {
        if(i==raws-1 && distr.rem>0)
        {
            hStep=workingArea->width()/distr.rem;
            curCol=distr.rem;
        }

        for(int j=0;j<curCol;++j)
        {
            dockables[i*cols+j]->setX(hStep*j/2);
            dockables[i*cols+j]->setY(vStep*i/2);
            dockables[i*cols+j]->setSize(QSizeF(hStep,vStep));
            dockables[i*cols+j]->update();
        }
    }

    return true;
}

void VNAAppWindow::resizeEvent(QResizeEvent *event)
{
    BasicWindow::resizeEvent(event);
    arrangeDockables();
    dockArea->setPosition(QPointF(0,0));
    dockArea->setSize(workingArea->size());
}

void VNAAppWindow::mouseMoveEvent(QMouseEvent *event)
{
    BasicWindow::mouseMoveEvent(event);
}

DockingPlaceItem *VNAAppWindow::getDockArea() const
{
    return dockArea;
}
