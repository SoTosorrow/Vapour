#pragma once
#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include<QGraphicsView>
#include<QGraphicsItem>
#include<QWidget>
#include<QtGui>
#include<QGraphicsScene>
#include<QRectF>
#include<QDebug>
#include<QMouseEvent>
#include<QKeyEvent>
#include<typeinfo>

//TODO： #include<QDataStream>   序列化与反序列化

#include"editor_scene.h"


class EditorView : public QGraphicsView
{
public:
    EditorView(EditorScene* scene,QWidget *parent=nullptr);
    ~EditorView();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;  // 鼠标滑轮影响场景大小


    void middleMouseButtonPress(QMouseEvent *event);
    void middleMouseButtonRelease(QMouseEvent *event);
    void leftMouseButtonPress(QMouseEvent *event);
    void LeftMouseButtonRelease(QMouseEvent *event);
    void RightMouseButtonPress(QMouseEvent *event);
    void RightMouseButtonRelease(QMouseEvent *event);


    void addNode(const int index);
    void addNode(const int index,const int type);
    void addEdge(int start_node_index,int start_socket_index,
                 int end_node_index,int end_socket_index);

    void buildGraph();
    void ergodicGraph();



//    QGraphicsItem* NodeToItem(NodeEnsemble* node);
//    QGraphicsItem* EdgeToItem(NodeEdge* edge);

public:
//    friend QDataStream &operator<<(QDataStream &,const EditorView &);
//    friend QDataStream &operator>>(QDataStream &,EditorView &);


public:
    EditorScene* editorScene;    //绘制背景
//    QVector<std::shared_ptr<NodeEnsemble>> nodes;
//    QVector<std::shared_ptr<NodeEdge>> edges;
//    std::shared_ptr<NodeEdge> edge;
//    std::shared_ptr<NodeEdgeTemp> edge_temp;

//    QVector<bool> visited;
//    QQueue<std::shared_ptr<NodeEnsemble>> queue;

    bool is_edge_temp_alive = false;
    int number = 100;   // prime index

//    std::shared_ptr<QGraphicsItem> obj;
//    std::shared_ptr<QGraphicsItem> item;
    // 寻找智能指针或者其他替代方法
    QGraphicsItem* obj;
    QGraphicsItem* item;

    bool output_ready = false;
    bool input_ready = false;
    int input_node_index;
    int input_socket_index;
    int output_node_index;
    int output_socket_index;


private:
    // 缩放参数
    float zoomInFactor = 1.25;
    int zoom = 0;
    int zoomStep = 1;
    int zoomRange[2] = {-8,3};
    BOOLEAN zoomClamp = true;

};


#endif // EDITORVIEW_H
