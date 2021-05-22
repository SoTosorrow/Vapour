#include "vapour_edge.h"



VapourEdge::VapourEdge(VapourNode *start_node, VapourNode *end_node, VapourSocket *start_socket, VapourSocket *end_socket, QGraphicsItem *parent)
    :QGraphicsPathItem()
{
    Q_UNUSED(parent);
    qDebug()<<"Create: Edge";
    this->input_node = start_node;
    this->output_node = end_node;
    this->input_socket = start_socket;
    this->output_socket = end_socket;

    this->start_socket_pos = start_socket->pos();
    this->end_socket_pos = end_socket->pos();
    this->start_pos = start_node->desc->getPos() + start_socket_pos;
    this->end_pos = end_node->desc->getPos() + end_socket_pos;
    this->path = QPainterPath(start_pos);

    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

VapourEdge::VapourEdge(const VapourEdge &edge)
    :QGraphicsPathItem()
{
    this->index = edge.index;
    this->input_node = edge.input_node;
    this->output_node = edge.output_node;
    this->input_socket = edge.input_socket;
    this->output_socket = edge.output_socket;
    this->start_pos = edge.start_pos;
    this->end_pos = edge.end_pos;
    this->start_socket_pos = edge.start_socket_pos;
    this->end_socket_pos = edge.end_socket_pos;
    this->path = edge.path;
}

void VapourEdge::operator=(const VapourEdge &edge)
{
    this->index = edge.index;
    this->input_node = edge.input_node;
    this->output_node = edge.output_node;
    this->input_socket = edge.input_socket;
    this->output_socket = edge.output_socket;
    this->start_pos = edge.start_pos;
    this->end_pos = edge.end_pos;
    this->start_socket_pos = edge.start_socket_pos;
    this->end_socket_pos = edge.end_socket_pos;
    this->path = edge.path;
}

VapourEdge::~VapourEdge()
{
    qDebug()<<"Delete: Edge";
    this->output_socket->is_connected=false;
    // can not delete the pointer
    this->input_node = nullptr;
    this->output_node = nullptr;
    this->input_socket = nullptr;
    this->output_socket = nullptr;
}

void VapourEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen1(QColor("#aaaaaa"));
    pen1.setWidth(2);
    QPen pen2(QColor("#228B22"));
    pen2.setWidth(2);
    this->start_pos = this->input_node->desc->getPos() + start_socket_pos;
    this->end_pos = this->output_node->desc->getPos() + end_socket_pos;
    path = QPainterPath(start_pos);


    // Direct / Bezier
    painter->setRenderHint(QPainter::Antialiasing);
    if(!this->isSelected()){
        //painter->setPen(QPen(QColor("#aaaaaa")));
        painter->setPen(pen1);
    }
    else{
        // painter->setPen(QPen(QColor(Qt::red)));
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

QRectF VapourEdge::boundingRect() const
{
    return this->path.boundingRect();
}
