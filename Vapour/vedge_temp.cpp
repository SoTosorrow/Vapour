#include "vedge_temp.h"


VEdgeTemp::VEdgeTemp(QPointF start, QPointF end, QGraphicsItem *parent)
{
    Q_UNUSED(parent);
    this->_startPos = start;
    this->_endPos = end;
    this->_path = QPainterPath(_startPos);
}

VEdgeTemp::VEdgeTemp(const VEdgeTemp &edge)
{
    Q_UNUSED(edge);
}

void VEdgeTemp::operator=(const VEdgeTemp &edge)
{
    Q_UNUSED(edge);
}


void VEdgeTemp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen1(QColor("#aaaaaa"));
    pen1.setWidth(2);
    pen1.setStyle(Qt::DashLine);

    this->_path = QPainterPath(_startPos);
    painter->setPen(pen1);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);

    qreal distance = (_endPos.x() - _startPos.x()) * 0.5;
    if(_startPos.x() > _endPos.y()&&_startPos.y() > _endPos.x()){
        distance *= -1;
    }

    _path.moveTo(_startPos);
    _path.cubicTo(_startPos.x() + distance,
                  _startPos.y(),
                  _endPos.x() - distance,
                  _endPos.y(),
                  _endPos.x(),
                  _endPos.y());
    this->setPath(_path);
    painter->drawPath(_path);
}

QRectF VEdgeTemp::boundingRect() const
{
    return this->_path.boundingRect();
}

void VEdgeTemp::setEndPos(QPointF end)
{
    this->_endPos = end;
}

void VEdgeTemp::setStartPos(QPointF start)
{
    this->_startPos = start;
}
