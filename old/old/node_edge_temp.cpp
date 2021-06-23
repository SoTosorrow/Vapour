#include "node_edge_temp.h"


NodeEdgeTemp::NodeEdgeTemp(QPointF start,QPointF end, QGraphicsItem *parent)
    //:QGraphicsPathItem(parent)
//  为什么会偏离  加上了父级的位置？
{
    Q_UNUSED(parent);
    this->start_pos = start;
    this->end_pos = end;
    this->path = QPainterPath(start_pos);
    //this->setFlag(QGraphicsItem::ItemIsSelectable);
}


NodeEdgeTemp::NodeEdgeTemp(const NodeEdgeTemp &nodeEdge):QGraphicsPathItem()
{
    Q_UNUSED(nodeEdge);

}

void NodeEdgeTemp::operator=(const NodeEdgeTemp &nodeEdge)
{
    Q_UNUSED(nodeEdge);
}

NodeEdgeTemp::~NodeEdgeTemp()
{
}

void NodeEdgeTemp::setEndPos(QPointF end)
{
    this->end_pos = end;
}

void NodeEdgeTemp::setStartPos(QPointF start)
{
    this->end_pos = start;
}


void NodeEdgeTemp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen1(QColor("#aaaaaa"));
    pen1.setWidth(2);
    pen1.setStyle(Qt::DashLine);

    this->path = QPainterPath(start_pos);
    painter->setPen(pen1);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);

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
    this->setPath(path);
    painter->drawPath(path);
}

QRectF NodeEdgeTemp::boundingRect() const
{
    return this->path.boundingRect();
    //return this->shape().boundingRect();

}
