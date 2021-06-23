#pragma once
#ifndef VVIEW_H
#define VVIEW_H

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

#include "vscene.h"
#include "vcomputethread.h"
#include "vnode.h"
#include "vedge.h"
#include "vedge_temp.h"
#include "vsocket.h"
#include "vnode_develop.h"
#include "vnode_cv.h"

class VView : public QGraphicsView
{
public:
    VView(VScene* scene,QWidget *parent=nullptr);
    ~VView();

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

    void addEdge(VNode* startNode,VNode* endNode,
                 VSocket* startSocket,VSocket* endSocket);
    void deleteItem();
    void copyItem();
    void queryNodeInfo();
    void ergodicGraph();
    void debugTest();

private slots:
    void addNode(int index, QPoint pos);
    void addNode(int index, int type, QPoint pos);
    VNode *addAndGetNode(int index, int type, QPoint pos);

private:
    VScene* _scene;
    VComputeThread* _computeThread;

    QList<VNode*> _nodes;
    QList<VEdge*> _edges;

    VEdgeTemp* _edgeTemp;
    VEdge* _edge;

    QMenu* _mainMenu;
    QList<QAction*> _action;

    // add edge need
    VNode* _startNode;
    VNode* _endNode;
    VSocket* _startSocket;
    VSocket* _endSocket;

    bool _isEdgeTempAlive = false;
    int _number = 100;

    // zoom scale
    float _zoomInFactor = 1.25;
    int _zoom = 0;
    int _zoomStep = 1;
    int _zoomRange[2] = {-8,3};
    bool _zoomClamp = true;

};

#endif // VVIEW_H
