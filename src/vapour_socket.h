#pragma once
#ifndef VAPOURSOCKET_H
#define VAPOURSOCKET_H

// 节点输入输出端口的UI
#include<QGraphicsItem>
#include<QColor>
#include<QtGui>
#include<QDebug>
#include<QGraphicsSceneMouseEvent>
#include"vapour_types.h"

class VapourSocket : public QGraphicsItem
{
public:
    VapourSocket(QGraphicsItem *parent = nullptr);
    VapourSocket(const VapourSocket &socket,QGraphicsItem *parent = nullptr);
    void operator=(const VapourSocket &socket);
    ~VapourSocket();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect()const override;
    bool contains(const QPointF &point) const override;

    void setIndex(int index){
        this->index = index;
    }
    void setConnectType(VapourSocketConnectType socket_connect_type){
        this->socket_connect_type = socket_connect_type;
    }
    void setType(VapourSocketType socket_type){
        this->socket_type = socket_type;
    }

    int index;
    VapourSocketConnectType socket_connect_type;
    VapourSocketType socket_type;




private:
    // paint 相关
    float radius = 6.0;
    QColor color_basic;// socket 颜色  basic:number, image:image
    QColor color_outline;
    QPen pen;
    QBrush brush;

};

#endif // VAPOURSOCKET_H
