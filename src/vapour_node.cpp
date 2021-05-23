#include "vapour_node.h"


VapourNode::VapourNode(QWidget *parent)
    :QWidget(parent)
{
    // qDebug()<<"Create: Basic Vapour-node";
    initDesc(1,1);
    this->desc = new VapourDescriptorInput(input_socket_number,output_socket_number,"test",1);
    setTitle("nothing here");
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
    qDeleteAll(input_datas);
    qDeleteAll(output_datas);
    // delete connect_info
    delete desc;
    input_nodes.clear();
    output_nodes.clear();
    input_datas.clear();
    output_datas.clear();
    desc = nullptr;
}
