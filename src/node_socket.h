#pragma once
#ifndef NODESOCKET_H
#define NODESOCKET_H


#include<QGraphicsItem>
#include<QColor>
#include<QtGui>
#include<QDebug>
#include<QGraphicsSceneMouseEvent>

#include"types.h"


class NodeSocket:public QGraphicsItem
{
public:
    NodeSocket(DATA_TYPE data_type=DATA_NUMBER,QGraphicsItem *parent = nullptr);
    NodeSocket(const NodeSocket &socket,QGraphicsItem *parent = nullptr);
    ~NodeSocket();
    void operator=(const NodeSocket &socket);


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect()const override;
    bool contains(const QPointF &point) const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


    void setType(SOCKET_TYPE type);
    void setDataType(DATA_TYPE type);
    void setIndex(int index);

    enum SOCKET_TYPE socket_type;
    enum DATA_TYPE data_type;
    int index=-1;
    bool is_connected = false;
    //QList<NodeSocket*> connect_sockets;



private:
    // paint 相关
    float radius = 6.0;
    QColor color_basic;// socket 颜色  basic:number, image:image
    QColor color_outline;
    QPen pen;
    QBrush brush;
};
#endif // NODESOCKET_H
