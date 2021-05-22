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
// #include<typeinfo>
#include<QMenu>
#include<QQueue>

//TODO： #include<QDataStream>   序列化与反序列化

#include"editor_scene.h"
#include"node.h"
#include"node_edge_temp.h"
#include"node_edge.h"


class EditorView : public QGraphicsView
{
    Q_OBJECT
public:
    EditorView(EditorScene* scene,QWidget *parent=nullptr);
    ~EditorView();

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


//    void addNode(QPoint pos);
//    void addNode();
    void addEdge(Node* input_node,Node* output_node,
                 NodeSocket* input_socket,NodeSocket* output_socket);
    void deleteItem();
    //void deleteEdge(Node *node);
    void QueryNode();

    void buildGraph();
    void ergodicGraph();



public:
//    friend QDataStream &operator<<(QDataStream &,const EditorView &);
//    friend QDataStream &operator>>(QDataStream &,EditorView &);


public:
    EditorScene* editorScene;    //绘制背景
    QList<Node*> nodes;
    QList<NodeEdge*> edges;
    NodeEdgeTemp* edge_temp;
    NodeEdge *edge;

    Node* start_node;
    Node* end_node;
    NodeSocket* start_socket;
    NodeSocket* end_socket;

    QMenu *menu;
    QList<QAction*> action;


    bool is_edge_temp_alive = false;
    int number = 100;   // prime index


private slots:
    void addNode();
    void addNode(int index,QPoint pos);
    void addNode(int index,int type,QPoint pos);

private:
    // 缩放参数
    float zoomInFactor = 1.25;
    int zoom = 0;
    int zoomStep = 1;
    int zoomRange[2] = {-8,3};
    BOOLEAN zoomClamp = true;

};


#endif // EDITORVIEW_H
