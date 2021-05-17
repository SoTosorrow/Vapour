#pragma once
#ifndef NODE_H
#define NODE_H

#include<QGraphicsScene>
#include<QWidget>
#include<QList>

#include"node_item.h"

class Node : public QWidget
{
public:
    Node(QWidget *parent=nullptr);
    ~Node();

    Node(const Node& node,QWidget *parent=nullptr);
    void operator=(const Node &node);

    void setPos(QPointF pos);


public:
    int index;
//    QList<Node*> input_nodes;
//    QList<Node*> output_nodes;
//    Node* input_node;
//    Node* output_node;

    NodeItem* item;

};

#endif // NODE_H
