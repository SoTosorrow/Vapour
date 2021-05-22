#include "vapour_node.h"


VapourNode::VapourNode(QWidget *parent)
    :QWidget(parent)
{
    //qDebug()<<"Create: Vapour-node";
    initDesc(1,1);
    this->desc = new VapourDescriptor(input_socket_number,output_socket_number,"test",1);

}

VapourNode::VapourNode(const VapourNode &node, QWidget *parent)
    :QWidget(parent)
{
    Q_UNUSED(node);
}

void VapourNode::operator=(const VapourNode &node)
{
     Q_UNUSED(node);
}

VapourNode::~VapourNode()
{
    qDebug()<<"Delete: VapourNode";
    qDeleteAll(input_nodes);
    qDeleteAll(output_nodes);
    // delete connect_info
    delete desc;
    input_nodes.clear();
    output_nodes.clear();
    desc = nullptr;
}
