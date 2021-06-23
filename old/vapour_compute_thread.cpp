#include "vapour_compute_thread.h"

VapourComputeThread::VapourComputeThread(QList<VapourNode*> nodes)
{
    this->nodes = nodes;
}

VapourComputeThread::~VapourComputeThread()
{
    qDeleteAll(nodes);
    nodes.clear();
}

void VapourComputeThread::run()
{
     qDebug()<<"Compute thread"<<QThread::currentThreadId();
     qDebug()<<"**************";
     QQueue<VapourNode*> queue;
     qDebug()<<"Compute Node init";
     for(int i=0;i<this->nodes.length();i++){
         this->nodes[i]->initData();
         //for(int j=0;j<this->nodes[i]->input_nodes.length();j++)
         this->nodes[i]->input_vaild = this->nodes[i]->input_nodes.length();
         this->nodes[i]->output_vaild = this->nodes[i]->output_nodes.length();
         if(this->nodes[i]->input_vaild == 0){
             queue.append(this->nodes[i]);
         }
     }

     qDebug()<<"topological-sort start";
     while(!queue.empty()){
         qDebug()<<"Compute: "<<queue[0]->index;
         queue[0]->handle();
         queue[0]->transfer();
         for(int k=0;k<queue[0]->output_nodes.length();k++){
             queue[0]->output_nodes[k]->input_vaild--;
             if(queue[0]->output_nodes[k]->input_vaild == 0){
                 queue.append(queue[0]->output_nodes[k]);
             }
         }
         queue.pop_front();
     }
     qDebug()<<"Compute Node Complete";
}
