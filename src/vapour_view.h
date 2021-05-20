#ifndef VAPOURVIEW_H
#define VAPOURVIEW_H

#include<QGraphicsView>
#include<QGraphicsItem>
#include<QWidget>
#include<QtGui>
#include<QGraphicsScene>
#include<QRectF>
#include<QDebug>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QMenu>
#include<QQueue>
#include"vapour_scene.h"
#include"vapour_descriptor.h"

class VapourView : public QGraphicsView
{
public:
    VapourView(VapourScene* scene,QWidget *parent=nullptr);
    ~VapourView();

    void debug();

public:
    VapourScene* vapour_scene;




private:
    // 缩放参数
    float zoomInFactor = 1.25;
    int zoom = 0;
    int zoomStep = 1;
    int zoomRange[2] = {-8,3};
    BOOLEAN zoomClamp = true;
};

#endif // VAPOURVIEW_H
