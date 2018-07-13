#include "vnaappwindow.h"
#include <math.h>
#include <stdlib.h>


VNAAppWindow::VNAAppWindow(QWindow *parent):
    BasicWindow(parent)
{
    for(int i=0; i<21; i++)
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

    qreal rRows=std::sqrt(dockablesNum/ratio);
    int rows=rRows>=dockablesNum?dockablesNum:std::ceil(rRows);
    int columns=std::ceil(dockablesNum/rows);

    std::div_t distr=std::div(dockablesNum,columns);

    qreal vStep=workingArea->height()/rows;
    qreal hStep=workingArea->width()/columns;

    int curCol=columns;

    for(int i=0; i<rows; ++i)
    {
        if(i==rows-1 && distr.rem>0)
        {
            hStep=workingArea->width()/distr.rem;
            curCol=distr.rem;
        }

        for(int j=0;j<curCol;++j)
        {
            dockables[i*columns+j]->setX(hStep*j/2);
            dockables[i*columns+j]->setY(vStep*i/2);
            dockables[i*columns+j]->setSize(QSizeF(hStep,vStep));
            dockables[i*columns+j]->update();
        }
    }

    return true;
}

void VNAAppWindow::resizeEvent(QResizeEvent *event)
{
    BasicWindow::resizeEvent(event);

    arrangeDockables();
//    if(!arrangeDockables())
//    {
//        setHeight(event->oldSize().height());
//        setWidth(event->oldSize().width());
//    }
}
