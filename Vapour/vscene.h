#pragma once
#ifndef VSCENE_H
#define VSCENE_H

/*
    @author:Sotosorrow
    @at:2021-6-22
    Draw backGround
    finished

*/
#include<QWidget>
#include<QGraphicsScene>
#include<QColor>
#include<QLine>
#include<QPen>
#include<QPainter>
#include<QRectF>
#include<QDebug>
#include<math.h>

class VScene : public QGraphicsScene
{
public:
    VScene(QWidget *parent=nullptr);
    ~VScene();

    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void setSceneSize(int width,int height)
    {
        this->setSceneRect(-width/2,-height/2,width,height);
    }
private:
    // bg-draw style
    QColor _colorBackground;
    QColor _colorLight;
    QColor _colorDark;
    QPen _penLight;
    QPen _penDark;

    // bg-draw parameters
    int _gridSize=20;
    int _gridSquare=5;
    int _sceneWidth = 6400;
    int _sceneHeight = 6400;

    int _left;
    int _right;
    int _top;
    int _bottom;
    int _primeLeft;
    int _primeTop;
};

#endif // VSCENE_H
