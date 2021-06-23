#include "editor_scene.h"

EditorScene::EditorScene(QWidget *parent)
    :QGraphicsScene(parent)
{

    this->color_background = QColor("#393939");
    this->color_light = QColor("#2f2f2f");
    this->color_dark = QColor("#262626");
    this->pen_light = QPen(this->color_light);
    this->pen_dark = QPen(this->color_dark);
    this->pen_light.setWidth(1);
    this->pen_dark.setWidth(2);

    this->setBackgroundBrush(this->color_background); // 背景颜色

    //设置场景总大小
    this->SetScene(this->scene_width,this->scene_height);
    //this->setSceneRect(-this->scene_width/2,-this->scene_height/2,this->scene_width,this->scene_height);

}
EditorScene::~EditorScene()
{

}
//drawForeground
// TODO:thread
void EditorScene::drawBackground(QPainter *painter, const QRectF &rect){
    QGraphicsScene::drawBackground(painter,rect);
    this->left = floor(rect.left());
    this->right = ceil(rect.right());
    this->top = floor(rect.top());
    this->bottom = ceil(rect.bottom());
    this->prime_left = left - (left % this->gridSize);
    this->prime_top = top - (top % this->gridSize);

    //TODO vector或数组画线
    //painter->setPen(*pen_light);
    for (int i=prime_left;i<right ;i+=gridSize ) {
        if(i%(gridSize * gridSquare) != 0){
            painter->setPen(pen_light);
            painter->drawLine(i,top,i,bottom);
        }
        else{
            painter->setPen(pen_dark);
            painter->drawLine(i,top,i,bottom);
        }

    }
    //painter->setPen(*pen_dark);
    for (int i=prime_top;i<bottom ;i+=gridSize ) {
        if(i%(gridSize * gridSquare) != 0){
            painter->setPen(pen_light);
            painter->drawLine(left,i,right,i);
        }
        else{
            painter->setPen(pen_dark);
            painter->drawLine(left,i,right,i);
        }
    }

}

void EditorScene::SetScene(int width, int height)
{
    //设置场景总大小
    this->setSceneRect(-width/2,-height/2,width,height);

}
