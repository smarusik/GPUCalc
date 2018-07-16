#ifndef DRAGPROCESS_H
#define DRAGPROCESS_H

#include "moveprocess.h"

class DragProcess : public MoveProcess
{
public:
    DragProcess(quint32 hint, QQuickWindow *hW);
    //virtual bool updateRubberBand();

};

#endif // DRAGPROCESS_H
