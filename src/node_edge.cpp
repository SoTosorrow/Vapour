#include "node_edge.h"

NodeEdge::NodeEdge(std::shared_ptr<Node> start_node,std::shared_ptr<Node> end_node,
                   std::shared_ptr<NodeSocket> start_socket,std::shared_ptr<NodeSocket> end_socket,
                   QGraphicsItem *parent)
//  为什么会偏离  加上了父级的位置？
    //:QGraphicsPathItem(parent)
{
    Q_UNUSED(parent);
    qDebug()<<"Create: Edge";
    this->node_pair = std::make_pair(start_node,end_node);
    this->socket_pair = std::make_pair(start_socket,end_socket);
    this->start_socket_pos = start_socket->pos();
    this->end_socket_pos = end_socket->pos();
    this->start_pos = start_node->item->pos() + start_socket_pos;
    this->end_pos = end_node->item->pos() + end_socket_pos;
    this->path = std::make_shared<QPainterPath>(start_pos);

    this->setFlag(QGraphicsItem::ItemIsSelectable);

}
//NodeEdge::NodeEdge(std::shared_ptr<NodeSocket> start_socket,std::shared_ptr<NodeSocket> end_socket,
//                   QGraphicsItem *parent)
//    :QGraphicsPathItem(parent)
//{
//    this->node_pair = std::make_pair(start_socket->node_index,end_socket->node_index);
//    this->socket_pair = std::make_pair(start_socket,end_socket);

//}
NodeEdge::NodeEdge(const NodeEdge &node_edge)
    :QGraphicsPathItem()
{
    this->node_pair = node_edge.node_pair;
    this->socket_pair = node_edge.socket_pair;

}
void NodeEdge::operator=(const NodeEdge &node_edge)
{
    this->node_pair = node_edge.node_pair;
    this->socket_pair = node_edge.socket_pair;
}
NodeEdge::~NodeEdge()
{
    qDebug()<<"edge delete";
    this->node_pair.first.reset();
    this->node_pair.second.reset();
    this->socket_pair.first.reset();
    this->socket_pair.second.reset();

}
void NodeEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen1(QColor("#aaaaaa"));
    pen1.setWidth(2);
    QPen pen2(QColor("#FF0000"));
    pen2.setWidth(2);
    this->start_pos = this->node_pair.first->item->pos() + start_socket_pos;
    this->end_pos = this->node_pair.second->item->pos() + end_socket_pos;
    path = std::make_shared<QPainterPath>(start_pos);


    // Direct / Bezier
    painter->setRenderHint(QPainter::Antialiasing);
    if(!this->isSelected()){
        //painter->setPen(QPen(QColor("#aaaaaa")));
        painter->setPen(pen1);
    }
    else{
        //painter->setPen(QPen(QColor(Qt::red)));
        painter->setPen(pen2);
    }
    painter->setBrush(Qt::NoBrush);

//TODO when simplified and when *pen

    qreal distance = (end_pos.x() - start_pos.x()) * 0.5;
    if(start_pos.x() > end_pos.y()&&start_pos.y() > end_pos.x()){
        distance *= -1;
    }

    path->moveTo(start_pos);
    path->cubicTo(start_pos.x() + distance,
                  start_pos.y(),
                  end_pos.x() - distance,
                  end_pos.y(),
                  end_pos.x(),
                  end_pos.y());


    //path->lineTo(end_pos);
    this->setPath(*path.get());
    painter->drawPath(*path.get());

}

QRectF NodeEdge::boundingRect() const
{
    return this->path->boundingRect();
    //return this->shape().boundingRect();

}

void NodeEdge::setIndex(int index)
{
    this->index = index;
}

void NodeEdge::setStartPos(NodeSocket *start_socket)
{
    this->start_pos = start_socket->pos();
}

void NodeEdge::setEndPos(NodeSocket *end_socket)
{
    this->end_pos = end_socket->pos();
}
