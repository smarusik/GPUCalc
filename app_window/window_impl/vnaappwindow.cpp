#include "vnaappwindow.h"
#include <math.h>
#include <stdlib.h>


VNAAppWindow::VNAAppWindow(QWindow *parent):
    BasicWindow(parent)
{
    for(int i=0; i<7; i++)
    {
        BasicDockItem *item=new BasicDockItem(workingArea);

        dockables.push_back(item);
        item->setPosition(QPointF(i*50,i*50));
        item->setSize(QSizeF(100,100));
        item->update();
    }
}

bool VNAAppWindow::arrangeDockables()
{
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
}

void VNAAppWindow::mouseMoveEvent(QMouseEvent *event)
{
    BasicWindow::mouseMoveEvent(event);
}
