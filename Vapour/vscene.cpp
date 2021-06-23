#include "vscene.h"

VScene::VScene(QWidget *parent)
    :QGraphicsScene(parent)
{
    qDebug()<<"Create: VapourScene";
    this->_colorBackground = QColor("#393939");
    this->_colorLight = QColor("#2f2f2f");
    this->_colorDark = QColor("#262626");
    this->_penLight = QPen(this->_colorLight);
    this->_penDark = QPen(this->_colorDark);
    this->_penLight.setWidth(1);
    this->_penDark.setWidth(2);

    // set bg-color
    this->setBackgroundBrush(this->_colorBackground);
    this->setSceneSize(this->_sceneWidth,this->_sceneHeight);
}

VScene::~VScene()
{

}

void VScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter,rect);
    this->_left = floor(rect.left());
    this->_right = ceil(rect.right());
    this->_top = floor(rect.top());
    this->_bottom = ceil(rect.bottom());
    this->_primeLeft = _left - (_left % this->_gridSize);
    this->_primeTop = _top - (_top % this->_gridSize);

    //TODO vector或数组画线
    //painter->setPen(*pen_light);
    for (int i=_primeLeft;i<_right ;i+=_gridSize ) {
        if(i%(_gridSize * _gridSquare) != 0){
            painter->setPen(_penLight);
            painter->drawLine(i,_top,i,_bottom);
        }
        else{
            painter->setPen(_penDark);
            painter->drawLine(i,_top,i,_bottom);
        }

    }
    //painter->setPen(*pen_dark);
    for (int i=_primeTop;i<_bottom ;i+=_gridSize ) {
        if(i%(_gridSize * _gridSquare) != 0){
            painter->setPen(_penLight);
            painter->drawLine(_left,i,_right,i);
        }
        else{
            painter->setPen(_penDark);
            painter->drawLine(_left,i,_right,i);
        }
    }
}
