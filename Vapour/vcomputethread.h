#pragma once
#ifndef VCOMPUTETHREAD_H
#define VCOMPUTETHREAD_H

#include <QThread>
#include<QDebug>

#include "vnode.h"

class VComputeThread : public QThread
{
public:
    VComputeThread(QList<VNode*> nodes);
    ~VComputeThread();

protected:
    void run() override;

private:
    QList<VNode*> _nodes;
};

#endif // VCOMPUTETHREAD_H
