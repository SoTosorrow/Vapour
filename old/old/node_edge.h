#ifndef NODEEDGE_H
#define NODEEDGE_H


#include<QGraphicsPathItem>
#include"types.h"
#include"node.h"
#include"node_socket.h"
#include<utility>    // pair

/**
 * Edge 负责节点间连线的可视化与逻辑上的联通
 * 储存了前后连接的node与socket指针
 */

class NodeEdge : public QGraphicsPathItem
{
public:
    NodeEdge()=default;
    NodeEdge(Node *start_node,Node *end_node,
             NodeSocket *start_socket,NodeSocket *end_socket,
             QGraphicsItem *parent = nullptr);
    NodeEdge(const NodeEdge &node_edge);
    void operator=(const NodeEdge &node_edge);
    ~NodeEdge();
    int type() const override {return Type_NodeEdge;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;


    void setIndex(int index);
    void setStartPos(NodeSocket *start_socket);
    void setEndPos(NodeSocket *end_socket);




    int index;
    Node* input_node;
    Node* output_node;
    NodeSocket *input_socket;
    NodeSocket *output_socket;

    QPainterPath path;
    QPointF start_pos;
    QPointF end_pos;
    QPointF start_socket_pos;
    QPointF end_socket_pos;

};

#endif // NODEEDGE_H
