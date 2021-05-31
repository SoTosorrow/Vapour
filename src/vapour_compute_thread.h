#ifndef VAPOURCOMPUTETHREAD_H
#define VAPOURCOMPUTETHREAD_H

#include <QThread>
#include<QDebug>
#include"vapour_node_develop.h"

class VapourComputeThread : public QThread
{
public:
    VapourComputeThread(QList<VapourNode*> nodes);
    ~VapourComputeThread();

protected:
    void run() override;
    QList<VapourNode*> nodes;
};

#endif // VAPOURCOMPUTETHREAD_H
