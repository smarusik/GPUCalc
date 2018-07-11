#ifndef STATUSBARITEM_H
#define STATUSBARITEM_H

#include "base_items/basicbaritem.h"

class StatusBarItem : public BasicBarItem
{
    Q_OBJECT
public:
    StatusBarItem(QQuickItem *parent=nullptr);
};

#endif // STATUSBARITEM_H
