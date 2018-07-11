#ifndef VNAAPPWINDOW_H
#define VNAAPPWINDOW_H

#include "base_windows/basicwindow.h"
#include <QObject>
#include <list>

class VNAAppWindow : public BasicWindow
{
    Q_OBJECT
public:
    VNAAppWindow(QWindow *parent=nullptr);

    virtual ~VNAAppWindow()
    {}

private:
    std::list<BasicWindow*> dockables;
};



#endif // VNAAPPWINDOW_H
