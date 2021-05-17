#include "node.h"

Node::Node(QWidget *parent)
    :QWidget(parent)
{
    qDebug()<<"Create: Test-node";
    this->item = new NodeItem("test");
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
