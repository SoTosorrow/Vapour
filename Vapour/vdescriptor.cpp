#include "vdescriptor.h"


VDescriptor::VDescriptor()
    :QGraphicsItem()
{
    // qDebug()<<"Create:"<<node_name;
    this->_title = QString("Basic Descriptor");
    this->_titleColor =QColor("#aaaaaa");
    this->_text =new QGraphicsTextItem(this->_title,this);
    this->_text->setDefaultTextColor(this->_titleColor);
    this->_text->setPos(4,2);
    this->_proxyContent = new QGraphicsProxyWidget(this);
    setSocketNumber(1,1);
    initSocket();

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

VDescriptor::VDescriptor(int inputNumber, int outputNumber, int editNumber)
    :QGraphicsItem()
{
    // qDebug()<<"Create:"<<node_name;
    this->_title = QString("Basic Descriptor");
    this->_titleColor =QColor("#aaaaaa");
    this->_text =new QGraphicsTextItem(this->_title,this);
    this->_text->setDefaultTextColor(this->_titleColor);
    this->_text->setPos(4,2);
    this->_proxyContent = new QGraphicsProxyWidget(this);

    // 定义socket数量
    setSocketNumber(inputNumber,outputNumber);
    // 定义socket
    initSocket();
//    setDescWidth(160);
//    setDescHeight(150);

    // 定义交互部分
    this->_interaction = new VActionEdit(editNumber);
    this->_interaction->setGeometry(_edgeSize, _titleHeight+0.5*_edgeSize,
                               _width - 2*_edgeSize,_height - 2*_edgeSize - _titleHeight);
    this->_proxyContent->setWidget(this->_interaction);

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemIsMovable);
}


VDescriptor::VDescriptor(const VDescriptor &desc)
    :QGraphicsItem()
{
    this->_text = desc._text;
    this->_titleColor = desc._titleColor;
    this->_proxyContent = desc._proxyContent;
}

void VDescriptor::operator=(const VDescriptor &desc)
{
    this->_text = desc._text;
    this->_titleColor = desc._titleColor;
    this->_proxyContent = desc._proxyContent;
}

VDescriptor::~VDescriptor()
{
    qDeleteAll(_inputSockets);
    qDeleteAll(_outputSockets);
    delete _interaction;
    delete _pathTitle;
    delete _pathData;
    delete _pathOutline;
    _inputSockets.clear();
    _outputSockets.clear();
    _interaction = nullptr;
    _pathTitle = nullptr;
    _pathData = nullptr;
    _pathOutline = nullptr;
}

void VDescriptor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    _pathTitle = new QPainterPath();
    _pathTitle->setFillRule(Qt::WindingFill);
    _pathTitle->addRoundedRect(0,0,_width,_titleHeight,_edgeSize,_edgeSize);//创建椭圆
    _pathTitle->addRect(0,_titleHeight-_edgeSize,_edgeSize,_edgeSize);//给椭圆左侧增加Rect遮住倒角
    _pathTitle->addRect(_width-_edgeSize,_titleHeight-_edgeSize,_edgeSize,_edgeSize);//给椭圆右侧增加Rect遮住倒角
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#FF313131")); // FF313131
    painter->drawPath(_pathTitle->simplified());

    _pathData = new QPainterPath();
    _pathData->setFillRule(Qt::WindingFill);
    _pathData->addRoundedRect(0,_titleHeight,_width,_height-_titleHeight,_edgeSize,_edgeSize);//创建椭圆
    _pathData->addRect(0,_titleHeight,_edgeSize,_edgeSize);//给椭圆左侧增加Rect遮住倒角
    _pathData->addRect(_width-_edgeSize,_titleHeight,_edgeSize,_edgeSize);//给椭圆右侧增加Rect遮住倒角
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#E3212121")); // #E3212121
    painter->drawPath(_pathData->simplified());



    _pathOutline =new QPainterPath();
    _pathOutline->addRoundedRect(0,0,_width,_height,_edgeSize,_edgeSize);
    if(!this->isSelected()){
        painter->setPen(QPen(QColor("#aaaaaa")));
    }
    else{
        painter->setPen(QPen(QColor(Qt::green)));
    }
    if(!this->_canCompute){
        painter->setPen(QPen(QColor(Qt::red)));
    }
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(_pathOutline->simplified());

    delete this->_pathTitle;
    this->_pathTitle = nullptr;
    delete this->_pathData;
    this->_pathData = nullptr;
    delete this->_pathOutline;
    this->_pathOutline = nullptr;
}

QRectF VDescriptor::boundingRect() const
{
    return QRectF(
        0,
        0,
        _width,
        _height
                );
}

bool VDescriptor::contains(const QPointF &point) const
{
    qreal right = this->pos().x() + _width+10;
    qreal bottom = this->pos().y() + _height;
    qreal left = this->pos().x()-10;
    qreal top = this->pos().y();
    if(point.x()>left&&point.x()<right && point.y()>top&&point.y()<bottom){
        return true;
    }
    return false;
}

void VDescriptor::initSocket()
{
    for(int i=0;i<this->_inputSocketNumber;i++){
        // temp是否正确释放
        VSocket* temp =  new VSocket(this);
        temp->setPos(0,i*30+40);
        temp->setIndex(i);
        _inputSockets.append(temp);
    }
    for(int j=0;j<this->_outputSocketNumber;j++){
        VSocket* temp =  new VSocket(this);
        temp->setPos(_width,j*20+34);
        temp->setIndex(j);
        _outputSockets.append(temp);
    }
}



