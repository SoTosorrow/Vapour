#ifndef NODEEDGETEMP_H
#define NODEEDGETEMP_H



#include<QGraphicsPathItem>
#include"types.h"
#include"node_socket.h"
#include<utility>    // pair

/**
 * EdgeTemp 负责节点间 预连线的可视化
 * 仅仅储存了前后连接的node与socket位置
 * 同一时间仅会存在一条
 */

class NodeEdgeTemp : public QGraphicsPathItem
{
public:
    NodeEdgeTemp()=default;
    NodeEdgeTemp(QPointF start,QPointF end,QGraphicsItem *parent = nullptr);
    NodeEdgeTemp(const NodeEdgeTemp &nodeEdge);
    void operator=(const NodeEdgeTemp &nodeEdge);
    ~NodeEdgeTemp();

    void setEndPos(QPointF end);
    void setStartPos(QPointF start);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;



    QPointF start_pos;
    QPointF end_pos;
    QPainterPath path;

};
#endif // NODEEDGETEMP_H
