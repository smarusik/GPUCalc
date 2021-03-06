#include "channelwindow.h"

ChannelWindow::ChannelWindow(QWindow *parent):
    BasicWindow(parent)
{
    connect(this,&QWindow::xChanged,this,&ChannelWindow::onXChanged);
    connect(this,&QWindow::yChanged,this,&ChannelWindow::onYChanged);
}

void ChannelWindow::resizeEvent(QResizeEvent *event)
{
    BasicWindow::resizeEvent(event);
}

void ChannelWindow::mouseMoveEvent(QMouseEvent *event)
{
    BasicWindow::mouseMoveEvent(event);
}

void ChannelWindow::onXChanged(int x)
{
//    qDebug()<<x;
}

void ChannelWindow::onYChanged(int y)
{
//    qDebug()<<y;
}
