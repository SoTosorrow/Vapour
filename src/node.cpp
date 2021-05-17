#include "node.h"

Node::Node(QWidget *parent)
    :QWidget(parent)
{
    qDebug()<<"Create: Test-node";
    this->item = new NodeItem("test");

    initSocket(2,1);
}

Node::~Node()
{
    qDebug()<<"Delete: Node";
    delete this->item;
    this->item=nullptr;
}

Node::Node(const Node &node, QWidget *parent)
    :QWidget(parent)
{
    Q_UNUSED(node);
}

void Node::operator=(const Node &node)
{
    Q_UNUSED(node);
}

void Node::setPos(QPointF pos)
{
    this->item->setPos(pos);
}

void Node::setIndex(int index)
{
    this->index = index;
}

void Node::initSocket(int in, int out)
{
    this->input_socket_number =in;
    this->output_socket_number = out;
    for(int i=0;i<input_socket_number;i++){
        NodeSocket *socket = new NodeSocket(item);
        socket->setPos(0,i*20+34);
        socket->setIndex(i);
        socket->setType(SOCKET_INPUT);
        input_sockets.append(socket);
    }
    for(int i=0;i<output_socket_number; i++){

        NodeSocket *socket2 = new NodeSocket(item);
        socket2->setPos(180,i*20+34);
        socket2->setIndex(i);
        socket2->setType(SOCKET_OUTPUT);
        output_sockets.append(socket2);

    }
}
