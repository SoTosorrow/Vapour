#include "vapour_descriptor.h"

VapourDescriptor::VapourDescriptor(QString node_name)
    :QGraphicsItem()
{
    // qDebug()<<"Create:"<<node_name;
    this->title = node_name;
    this->title_color =QColor("#aaaaaa");
    this->text =new QGraphicsTextItem(this->title,this);
    this->text->setDefaultTextColor(this->title_color);
    this->text->setPos(4,2);
    this->proxyContent = new QGraphicsProxyWidget(this);
    setSocketNumber(1,1);
    initSocket();

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

VapourDescriptor::VapourDescriptor(int in_num, int out_num, QString node_name,int edit_number)
    :QGraphicsItem()
{
    // qDebug()<<"Create: VapourDescriptor"<<node_name;
    this->title = node_name;
    this->title_color =QColor("#aaaaaa");
    this->text =new QGraphicsTextItem(this->title,this);
    this->text->setDefaultTextColor(this->title_color);
    this->text->setPos(4,2);
    this->proxyContent = new QGraphicsProxyWidget(this);

    // 定义socket数量
    setSocketNumber(in_num,out_num);
    // 定义socket
    initSocket();
//    setDescWidth(160);
//    setDescHeight(150);

    // 定义交互部分
    this->interaction = new VapourActionEdit(edit_number);
    this->interaction->setGeometry(edge_size, title_height+0.5*edge_size,
                               width - 2*edge_size,height - 2*edge_size - title_height);
    this->proxyContent->setWidget(this->interaction);

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

VapourDescriptor::VapourDescriptor(const VapourDescriptor &desc)
    :QGraphicsItem()
{
    this->text = desc.text;
    this->title_color = desc.title_color;
    this->proxyContent = desc.proxyContent;
}

void VapourDescriptor::operator=(const VapourDescriptor &desc)
{
    this->text = desc.text;
    this->title_color = desc.title_color;
    this->proxyContent = desc.proxyContent;
}

VapourDescriptor::~VapourDescriptor()
{
    qDeleteAll(input_sockets);
    qDeleteAll(output_sockets);
    input_sockets.clear();
    output_sockets.clear();
    delete interaction;
    interaction = nullptr;
    delete path_title;
    path_title = nullptr;
    delete path_data;
    path_data = nullptr;
    delete path_outline;
    path_outline = nullptr;


}

void VapourDescriptor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    path_title = new QPainterPath();
    path_title->setFillRule(Qt::WindingFill);
    path_title->addRoundedRect(0,0,width,title_height,edge_size,edge_size);//创建椭圆
    path_title->addRect(0,title_height-edge_size,edge_size,edge_size);//给椭圆左侧增加Rect遮住倒角
    path_title->addRect(width-edge_size,title_height-edge_size,edge_size,edge_size);//给椭圆右侧增加Rect遮住倒角
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#FF313131")); // FF313131
    painter->drawPath(path_title->simplified());

    path_data = new QPainterPath();
    path_data->setFillRule(Qt::WindingFill);
    path_data->addRoundedRect(0,title_height,width,height-title_height,edge_size,edge_size);//创建椭圆
    path_data->addRect(0,title_height,edge_size,edge_size);//给椭圆左侧增加Rect遮住倒角
    path_data->addRect(width-edge_size,title_height,edge_size,edge_size);//给椭圆右侧增加Rect遮住倒角
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#E3212121")); // #E3212121
    painter->drawPath(path_data->simplified());



    path_outline =new QPainterPath();
    path_outline->addRoundedRect(0,0,width,height,edge_size,edge_size);
    if(!this->isSelected()){
        painter->setPen(QPen(QColor("#aaaaaa")));
    }
    else{
        painter->setPen(QPen(QColor(Qt::green)));
    }
    if(!this->can_compute){
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

QRectF VapourDescriptor::boundingRect() const
{
    return QRectF(
        0,
        0,
        width,
        height
                );
}

bool VapourDescriptor::contains(const QPointF &point) const
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
