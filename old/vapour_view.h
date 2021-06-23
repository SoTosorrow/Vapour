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
#include"vapour_node_develop.h"
#include"vapour_node_cv.h"
#include"vapour_edge.h"
#include"vapour_edge_temp.h"
#include"vapour_types.h"
#include"vapour_compute_thread.h"

class VapourView : public QGraphicsView
{
public:
    VapourView(VapourScene* scene,QWidget *parent=nullptr);
    ~VapourView();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;  // 鼠标滑轮影响场景大小
    void contextMenuEvent(QContextMenuEvent *event) override;


    void middleMouseButtonPress(QMouseEvent *event);
    void middleMouseButtonRelease(QMouseEvent *event);
    void leftMouseButtonPress(QMouseEvent *event);
    void LeftMouseButtonRelease(QMouseEvent *event);
    void RightMouseButtonPress(QMouseEvent *event);
    void RightMouseButtonRelease(QMouseEvent *event);

    void addEdge(VapourNode* input_node,VapourNode* output_node,
                 VapourSocket* input_socket,VapourSocket* output_socket);
    void deleteItem();
    void copyNode();
    void queryNodeInfo();
    void ergodicGraph();

    void debug();

private slots:
    void addNode(int index,QPoint pos);
    void addNode(int index,int type,QPoint pos);
    VapourNode* addAndGetNode(int index,int type,QPoint pos);

public:
    VapourComputeThread* vapour_compute_thread;
    VapourScene* vapour_scene;
    QList<VapourNode*> nodes;
    QList<VapourEdge*> edges;
    VapourEdgeTemp* edge_temp;
    VapourEdge* edge;
    bool is_edge_temp_alive = false;
    int number = 100;

    // edge create need
    VapourNode* start_node;
    VapourNode* end_node;
    VapourSocket* start_socket;
    VapourSocket* end_socket;

    // right menu
    QMenu *menu;
    QList<QAction*> action;


private:
    // 缩放参数
    float zoomInFactor = 1.25;
    int zoom = 0;
    int zoomStep = 1;
    int zoomRange[2] = {-8,3};
    BOOLEAN zoomClamp = true;
};

#endif // VAPOURVIEW_H
