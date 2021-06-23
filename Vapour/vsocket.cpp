#include "vsocket.h"

VSocket::VSocket(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    //qDebug()<<"Create: VapourSocket";

    _colorBasic = QColor(Qt::blue);
    _colorOutline = QColor(Qt::black);
    _pen = QPen(_colorOutline);
    _brush = QBrush(_colorBasic);
    _pen.setWidth(1);

//    this->edge_mode = EDGE_NOOP;
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

VSocket::VSocket(const VSocket &socket, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    this->_index = socket._index;

}

void VSocket::operator=(const VSocket &socket)
{
    this->_index = socket._index;
}

VSocket::~VSocket()
{

}

void VSocket::paint(QPainter *painter,
                    const QStyleOptionGraphicsItem *option,
                    QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    switch(_dataType){
        case VDataTypeBasic:
            _brush = QBrush(QColor(Qt::white));
            break;
        case VDataTypeDouble:
            _brush = QBrush(QColor(Qt::green));
            break;
        case VDataTypeString:
            _brush = QBrush(QColor(Qt::blue));
            break;
        case VDataTypeMat:
            _brush = QBrush(QColor(Qt::red));
            break;
    }
    painter->setPen(_pen);

    if(!this->isSelected()){
        painter->setPen(QPen(QColor("#aaaaaa")));
    }
    else{
        painter->setPen(QPen(QColor(Qt::green)));
    }
    painter->setBrush(_brush);
    painter->drawEllipse(-_radius,-_radius,2*_radius,2*_radius);
}

QRectF VSocket::boundingRect() const
{
    return QRectF(
                -_radius,
                -_radius,
                _radius * 2,
                _radius * 2
                );
}

bool VSocket::contains(const QPointF &point) const
{
    int x = this->parentItem()->x()+this->pos().x();
    int y = this->parentItem()->y()+this->pos().y();
    if(point.x()>x-_radius && point.x()<x+_radius &&
            point.y()>y-_radius && point.y()<y+_radius){
        return true;
    }
    return false;
}
