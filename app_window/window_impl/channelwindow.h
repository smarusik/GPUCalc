#ifndef CHANNELWINDOW_H
#define CHANNELWINDOW_H

#include "base_windows/basicwindow.h"
#include "interaction/wininteractstate.h"

class ChannelWindow : public BasicWindow
{
public:
    ChannelWindow(QWindow *parent=nullptr);
private:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void onXChanged(int x);
    void onYChanged(int y);
};


#endif // CHANNELWINDOW_H
