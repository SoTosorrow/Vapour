#ifndef VAPOUREDGE_H
#define VAPOUREDGE_H

#include<QGraphicsPathItem>
#include<QPen>
#include<QPainterPath>
#include<QPainter>
#include"vapour_node.h"
#include"vapour_socket.h"

class VapourEdge : public QGraphicsPathItem
{
public:
    VapourEdge()=default;
    VapourEdge(VapourNode* start_node,VapourNode* end_node,
               VapourSocket* start_socket,VapourSocket* end_socket,
               QGraphicsItem *parent = nullptr);
    VapourEdge(const VapourEdge& edge);
    void operator=(const VapourEdge &edge);
    ~VapourEdge();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

    void setIndex(int index){
        this->index = index;
    }
    void setStartPos(VapourSocket *socket){
        this->start_pos = socket->pos();
    }
    void setEndPos(VapourSocket *socket){
        this->end_pos = socket->pos();
    }

public:
    int index;
    VapourNode* input_node;
    VapourNode* output_node;
    VapourSocket *input_socket;
    VapourSocket *output_socket;

    QPainterPath path;
    QPointF start_pos;
    QPointF end_pos;
    QPointF start_socket_pos;
    QPointF end_socket_pos;

};

#endif // VAPOUREDGE_H
