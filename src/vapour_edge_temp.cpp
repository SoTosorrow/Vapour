#include "vapour_edge_temp.h"

VapourEdgeTemp::VapourEdgeTemp(QPointF start,QPointF end,QGraphicsItem *parent)
{
    Q_UNUSED(parent);
    this->start_pos = start;
    this->end_pos = end;
    this->path = QPainterPath(start_pos);
}

VapourEdgeTemp::VapourEdgeTemp(const VapourEdgeTemp &edge)
{
    Q_UNUSED(edge);
}

void VapourEdgeTemp::operator=(const VapourEdgeTemp &edge)
{
    Q_UNUSED(edge);
}

void VapourEdgeTemp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF VapourEdgeTemp::boundingRect() const
{
    return this->path.boundingRect();
}

void VapourEdgeTemp::setEndPos(QPointF end)
{
    this->end_pos = end;
}

void VapourEdgeTemp::setStartPos(QPointF start)
{
    this->start_pos = start;
}
