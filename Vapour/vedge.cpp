#include "vedge.h"
#include "vnode.h"


VEdge::VEdge(VNode *startNode, VNode *endNode, VSocket *startSocket,
             VSocket *endSocket, QGraphicsItem *parent)
    :QGraphicsPathItem()
{
    Q_UNUSED(parent);
    //qDebug()<<"Create: VapourEdge";
    this->_startNode = startNode;
    this->_endNode = endNode;
    this->_startSocket = startSocket;
    this->_endSocket = endSocket;

    this->_startSocketPos = startSocket->pos();
    this->_endSocketPos = endSocket->pos();
    this->_startPos = startNode->getDesc()->getPos() + _startSocketPos;
    this->_endPos = endNode->getDesc()->getPos() + _endSocketPos;
    this->_path = QPainterPath(_startPos);

    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

VEdge::VEdge(const VEdge &edge)
    :QGraphicsPathItem()
{
    this->_startNode = edge._startNode;
    this->_endNode = edge._endNode;
    this->_startSocket = edge._startSocket;
    this->_endSocket = edge._endSocket;
}

void VEdge::operator=(const VEdge &edge)
{
    this->_startNode = edge._startNode;
    this->_endNode = edge._endNode;
    this->_startSocket = edge._startSocket;
    this->_endSocket = edge._endSocket;
}

VEdge::~VEdge()
{
    qDebug()<<"Delete: VapourEdge";
    this->_startNode = nullptr;
    this->_endNode = nullptr;
    this->_startSocket = nullptr;
    this->_endSocket = nullptr;
}

void VEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen1(QColor("#aaaaaa"));
    pen1.setWidth(2);
    QPen pen2(QColor("#228B22"));
    pen2.setWidth(2);
    this->_startPos = this->_startNode->getDesc()->getPos() + _startSocketPos;
    this->_endPos = this->_endNode->getDesc()->getPos() + _endSocketPos;
    _path = QPainterPath(_startPos);


    // Bezier
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

    qreal distance = (_endPos.x() - _startPos.x()) * 0.5;
    if(_startPos.x() > _endPos.y()&&_startPos.y() > _endPos.x()){
        //distance *= -1;
    }

    _path.moveTo(_startPos);
    _path.cubicTo(_startPos.x() + distance,
                  _startPos.y(),
                  _endPos.x() - distance,
                  _endPos.y(),
                  _endPos.x(),
                  _endPos.y());

    //path->lineTo(end_pos);
    this->setPath(_path);
    painter->drawPath(_path);
}

QRectF VEdge::boundingRect() const
{
    return this->_path.boundingRect();
}
