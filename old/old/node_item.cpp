#include "node_item.h"

NodeItem::NodeItem(QString node_name)
    :QGraphicsItem()
{
    this->title = node_name;
    this->title_color =QColor("#aaaaaa");
    this->text =new QGraphicsTextItem(this->title,this);
    this->text->setDefaultTextColor(this->title_color);
    this->text->setPos(4,2);
    this->proxyContent = new QGraphicsProxyWidget(this);


    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

NodeItem::NodeItem(const NodeItem &node_item){
    this->text = node_item.text;
    this->title_color = node_item.title_color;
    this->proxyContent = node_item.proxyContent;
}
void NodeItem::operator=(const NodeItem &node_item){
    this->text = node_item.text;
    this->title_color = node_item.title_color;
    this->proxyContent = node_item.proxyContent;
}
NodeItem::~NodeItem(){
    delete this->inter;
    this->inter=nullptr;
    delete this->proxyContent;
    this->proxyContent=nullptr;

    delete this->text;
    this->text=nullptr;
    delete this->path_title;
    this->path_title = nullptr;
    delete this->path_data;
    this->path_data = nullptr;
    delete this->path_outline;
    this->path_outline = nullptr;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    path_title = new QPainterPath();
    path_title->setFillRule(Qt::WindingFill);
    path_title->addRoundedRect(0,0,width,title_height,edge_size,edge_size);//创建椭圆
    path_title->addRect(0,title_height-edge_size,edge_size,edge_size);//给椭圆左侧增加Rect遮住倒角
    path_title->addRect(width-edge_size,title_height-edge_size,edge_size,edge_size);//给椭圆右侧增加Rect遮住倒角
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#FF313131"));
    painter->drawPath(path_title->simplified());

    path_data = new QPainterPath();
    path_data->setFillRule(Qt::WindingFill);
    path_data->addRoundedRect(0,title_height,width,height-title_height,edge_size,edge_size);//创建椭圆
    path_data->addRect(0,title_height,edge_size,edge_size);//给椭圆左侧增加Rect遮住倒角
    path_data->addRect(width-edge_size,title_height,edge_size,edge_size);//给椭圆右侧增加Rect遮住倒角
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#E3212121"));
    painter->drawPath(path_data->simplified());



    path_outline =new QPainterPath();
    path_outline->addRoundedRect(0,0,width,height,edge_size,edge_size);
    if(!this->isSelected()){
        painter->setPen(QPen(QColor("#aaaaaa")));
    }
    else{
        painter->setPen(QPen(QColor("#FFFFA637")));
    }
    if(!this->canCompute){
        painter->setPen(QPen(QColor(Qt::red)));
    }
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path_outline->simplified());

    delete this->path_title;
    this->path_title = nullptr;
    delete this->path_data;
    this->path_data = nullptr;
    delete this->path_outline;
    this->path_outline = nullptr;
}

QRectF NodeItem::boundingRect() const{
    return QRectF(
        0,
        0,
        width,
        height
                );
}

bool NodeItem::contains(const QPointF &point) const
{
    qreal right = this->pos().x() + width+10;
    qreal bottom = this->pos().y() + height;
    qreal left = this->pos().x()-10;
    qreal top = this->pos().y();
    if(point.x()>left&&point.x()<right && point.y()>top&&point.y()<bottom){
        return true;
    }
    return false;

}

void NodeItem::setTitle(QString title)
{
    this->text->setPlainText(title);
}

