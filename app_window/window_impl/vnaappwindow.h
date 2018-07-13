#ifndef VNAAPPWINDOW_H
#define VNAAPPWINDOW_H

#include "base_windows/basicwindow.h"
#include "base_items/basicdockitem.h"
#include <QObject>
#include <QList>

class VNAAppWindow : public BasicWindow
{
    Q_OBJECT
public:
    VNAAppWindow(QWindow *parent=nullptr);

    virtual ~VNAAppWindow()
    {}

    void arrangeDockables();


private:
    virtual void resizeEvent(QResizeEvent *event) override;

    QList<BasicDockItem*> dockables;
};



#endif // VNAAPPWINDOW_H
