#ifndef VAPOUR_NODE_DEVELOP_H
#define VAPOUR_NODE_DEVELOP_H

#include"vapour_node.h"

class VapourNodeInput : public VapourNode
{
public:
    VapourNodeInput(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour-node-Input";
        initDesc(2,1);
        this->desc = new VapourDescriptor(input_socket_number,output_socket_number,"test");

    }

};








#endif // VAPOUR_NODE_DEVELOP_H
