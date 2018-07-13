#include "vnaappwindow.h"
#include <math.h>
#include <stdlib.h>


VNAAppWindow::VNAAppWindow(QWindow *parent):
    BasicWindow(parent)
{
    for(int i=0; i<101; i++)
    {
        BasicDockItem *item=new BasicDockItem(workingArea);

        dockables.push_back(item);
        item->setPosition(QPointF(i*50,i*50));
        item->setSize(QSizeF(100,100));
        item->update();
    }
}

void VNAAppWindow::arrangeDockables()
{
    qreal dockablesNum=dockables.size();
    qreal ratio=std::floor(workingArea->width()/workingArea->height()+.5);

    qreal rRows=std::sqrt(dockablesNum/ratio);

    int rows=std::ceil(rRows);
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
}

void VNAAppWindow::resizeEvent(QResizeEvent *event)
{
    BasicWindow::resizeEvent(event);
    arrangeDockables();
}
