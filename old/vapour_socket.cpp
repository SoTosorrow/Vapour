#include "vapour_socket.h"

VapourSocket::VapourSocket(QGraphicsItem *parent): QGraphicsItem(parent)
{
    //qDebug()<<"Create: VapourSocket";
    color_basic = QColor("#0088A8");
    color_outline = QColor(Qt::black);
    pen = QPen(color_outline);
    brush = QBrush(color_basic);
    pen.setWidth(1);

//    this->edge_mode = EDGE_NOOP;

    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

VapourSocket::VapourSocket(const VapourSocket &socket, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    //qDebug()<<"Copy: VapourSocket";
    this->index = socket.index;
    this->socket_connect_type = socket.socket_connect_type;
    this->socket_type = socket.socket_type;
}

void VapourSocket::operator=(const VapourSocket &socket)
{
    //qDebug()<<"Copy: VapourSocket";
    this->index = socket.index;
    this->socket_connect_type = socket.socket_connect_type;
    this->socket_type = socket.socket_type;
}

VapourSocket::~VapourSocket()
{

}

void VapourSocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen);

    if(!this->isSelected()){
        painter->setPen(QPen(QColor("#aaaaaa")));
    }
    else{
        painter->setPen(QPen(QColor(Qt::green)));
    }
    painter->setBrush(brush);
    painter->drawEllipse(-radius,-radius,2*radius,2*radius);
}

QRectF VapourSocket::boundingRect() const
{
    return QRectF(
                -radius,
                -radius,
                radius * 2,
                radius * 2
                );
}

bool VapourSocket::contains(const QPointF &point) const
{
    int x = this->parentItem()->x()+this->pos().x();
    int y = this->parentItem()->y()+this->pos().y();
    if(point.x()>x-radius && point.x()<x+radius && point.y()>y-radius && point.y()<y+radius){
        return true;
    }
    return false;
}
