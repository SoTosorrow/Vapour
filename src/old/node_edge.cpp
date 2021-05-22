#include "node_edge.h"

NodeEdge::NodeEdge(Node *start_node,Node *end_node,
                   NodeSocket *start_socket,NodeSocket *end_socket,
                   QGraphicsItem *parent)
//  为什么会偏离  加上了父级的位置？
    //:QGraphicsPathItem(parent)
{
    Q_UNUSED(parent);
    qDebug()<<"Create: Edge";
    this->input_node = start_node;
    this->output_node = end_node;
    this->input_socket = start_socket;
    this->output_socket = end_socket;

    this->start_socket_pos = start_socket->pos();
    this->end_socket_pos = end_socket->pos();
    this->start_pos = start_node->item->pos() + start_socket_pos;
    this->end_pos = end_node->item->pos() + end_socket_pos;
    this->path = QPainterPath(start_pos);

    this->setFlag(QGraphicsItem::ItemIsSelectable);

}

NodeEdge::NodeEdge(const NodeEdge &node_edge)
    :QGraphicsPathItem()
{
    this->index = node_edge.index;
    this->input_node = node_edge.input_node;
    this->output_node = node_edge.output_node;
    this->input_socket = node_edge.input_socket;
    this->output_socket = node_edge.output_socket;
    this->start_pos = node_edge.start_pos;
    this->end_pos = node_edge.end_pos;
    this->start_socket_pos = node_edge.start_socket_pos;
    this->end_socket_pos = node_edge.end_socket_pos;
    this->path = node_edge.path;

}
void NodeEdge::operator=(const NodeEdge &node_edge)
{
    this->index = node_edge.index;
    this->input_node = node_edge.input_node;
    this->output_node = node_edge.output_node;
    this->input_socket = node_edge.input_socket;
    this->output_socket = node_edge.output_socket;
    this->start_pos = node_edge.start_pos;
    this->end_pos = node_edge.end_pos;
    this->start_socket_pos = node_edge.start_socket_pos;
    this->end_socket_pos = node_edge.end_socket_pos;
    this->path = node_edge.path;
}
NodeEdge::~NodeEdge()
{
    qDebug()<<"edge delete";
    this->output_socket->is_connected=false;
    this->input_node = nullptr;
    this->output_node = nullptr;
    this->input_socket = nullptr;
    this->output_socket = nullptr;

}
void NodeEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen1(QColor("#aaaaaa"));
    pen1.setWidth(2);
    QPen pen2(QColor("#FF0000"));
    pen2.setWidth(2);
    this->start_pos = this->input_node->item->pos() + start_socket_pos;
    this->end_pos = this->output_node->item->pos() + end_socket_pos;
    path = QPainterPath(start_pos);


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

    path.moveTo(start_pos);
    path.cubicTo(start_pos.x() + distance,
                  start_pos.y(),
                  end_pos.x() - distance,
                  end_pos.y(),
                  end_pos.x(),
                  end_pos.y());


    //path->lineTo(end_pos);
    this->setPath(path);
    painter->drawPath(path);

}

QRectF NodeEdge::boundingRect() const
{
    return this->path.boundingRect();
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
