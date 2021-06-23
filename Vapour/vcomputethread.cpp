#include "vcomputethread.h"

VComputeThread::VComputeThread(QList<VNode *> nodes)
{
    this->_nodes = nodes;
}

VComputeThread::~VComputeThread()
{
    qDeleteAll(_nodes);
    _nodes.clear();
}

void VComputeThread::run()
{
    qDebug()<<"Compute thread"<<QThread::currentThreadId();
    qDebug()<<"**************";
    QQueue<VNode*> queue;
    qDebug()<<"Compute Node init";
    for(int i=0;i<this->_nodes.length();i++){
        this->_nodes[i]->initData();
        //for(int j=0;j<this->nodes[i]->input_nodes.length();j++)
        this->_nodes[i]->inputVaild = this->_nodes[i]->getInputNodes().length();
//        this->_nodes[i]->output_vaild = this->_nodes[i]->getOutputNodes().length();
        if(this->_nodes[i]->inputVaild == 0){
            queue.append(this->_nodes[i]);
        }
    }

    qDebug()<<"topological-sort start";
    while(!queue.empty()){
        qDebug()<<"Compute: "<<queue[0]->getIndex();
        queue[0]->handle();
        queue[0]->transfer();
        for(int k=0;k<queue[0]->getOutputNodes().length();k++){
            queue[0]->getOutputNodes()[k]->inputVaild--;
            if(queue[0]->getOutputNodes()[k]->inputVaild == 0){
                queue.append(queue[0]->getOutputNodes()[k]);
            }
        }
        queue.pop_front();
    }
    qDebug()<<"Compute Node Complete";
}
