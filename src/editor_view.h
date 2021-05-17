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
#include<QMenu>

//TODO： #include<QDataStream>   序列化与反序列化

#include"editor_scene.h"
#include"node.h"
#include"node_edge_temp.h"


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

    void buildGraph();
    void ergodicGraph();



public:
//    friend QDataStream &operator<<(QDataStream &,const EditorView &);
//    friend QDataStream &operator>>(QDataStream &,EditorView &);


public:
    EditorScene* editorScene;    //绘制背景
    QList<Node*> nodes;
    NodeEdgeTemp* edge_temp;
    // edges

    QMenu *menu;


    bool is_edge_temp_alive = false;
    int number = 100;   // prime index


    bool output_ready = false;
    bool input_ready = false;
    int input_node_index;
    int input_socket_index;
    int output_node_index;
    int output_socket_index;

private slots:
    void addNode();
    void addNode(QPoint pos);

private:
    // 缩放参数
    float zoomInFactor = 1.25;
    int zoom = 0;
    int zoomStep = 1;
    int zoomRange[2] = {-8,3};
    BOOLEAN zoomClamp = true;

};


#endif // EDITORVIEW_H
