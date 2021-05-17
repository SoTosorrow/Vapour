#include "node_socket.h"

NodeSocket::NodeSocket(QGraphicsItem *parent): QGraphicsItem(parent)
{
    //this->index = 0;
    //type = SOCKET_INPUT;
    color_basic = QColor(Qt::yellow);//"#FFFF7700"
    color_outline = QColor(Qt::black);
    pen = QPen(color_outline);
    brush = QBrush(color_basic);
    pen.setWidth(1);

//    this->edge_mode = EDGE_NOOP;

    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

NodeSocket::NodeSocket(const NodeSocket &socket,QGraphicsItem *parent): QGraphicsItem(parent){
    this->index = socket.index;
    this->socket_type = socket.socket_type;
}

void NodeSocket::operator=(const NodeSocket &socket){
    this->index = socket.index;
    this->socket_type = socket.socket_type;
}


NodeSocket::~NodeSocket()
{

}

void NodeSocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen);

    if(!this->isSelected()){
        painter->setPen(QPen(QColor("#aaaaaa")));
    }
    else{
        painter->setPen(QPen(QColor(Qt::red)));
    }
    painter->setBrush(brush);
    painter->drawEllipse(-radius,-radius,2*radius,2*radius);

}

QRectF NodeSocket::boundingRect() const
{
    return QRectF(
                -radius,
                -radius,
                radius * 2,
                radius * 2
                );
}
//TODO complete
bool NodeSocket::contains(const QPointF &point) const
{
    int x = this->parentItem()->x()+this->pos().x();
    int y = this->parentItem()->y()+this->pos().y();
    if(point.x()>x-radius && point.x()<x+radius && point.y()>y-radius && point.y()<y+radius){
        return true;
    }
    return false;
}

void NodeSocket::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"socket clicked";
//    if(edge_mode==EDGE_NOOP){
//        edge_mode = EDGE_DRAG;
//    }
    //qDebug()<<this->edge_mode;
    QGraphicsItem::mousePressEvent(event);
    // 拖拽前鼠标位置
    //mouse_start_pos = this->mapToScene(event->pos());
   // mouse_start_pos = this->pos()+this->parentItem()->pos();

}

void NodeSocket::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // 拖曳后位置
   // mouse_end_pos = this->mapToScene(event->pos());
    //判断是否连接到另一个socket
    //isUnderMouse()
    //NodeSocket::collidesWithItem(this)

//    if(edge_mode == EDGE_DRAG){
//        edge_mode = EDGE_NOOP;
//    }
    //qDebug()<<this->edge_mode;
    QGraphicsItem::mouseReleaseEvent(event);
    //qDebug()<<mouse_start_pos<<" "<<mouse_end_pos;
}

void NodeSocket::setType(SOCKET_TYPE type){
    this->socket_type = type;
}
void NodeSocket::setIndex(int index){
    this->index = index;
}
