#pragma once
#ifndef NODE_H
#define NODE_H

#include<QGraphicsScene>
#include<QWidget>
#include<QList>

#include"node_item.h"
#include"node_socket.h"
#include"shader/node_shader.h"

//struct NodeConnect{
//    Node *node;
//};


class Node : public QWidget
{
public:
    Node(QWidget *parent=nullptr);
    Node(int type,QWidget *parent=nullptr);
    ~Node();

    Node(const Node& node,QWidget *parent=nullptr);
    void operator=(const Node &node);

    void setPos(QPointF pos);
    void setIndex(int index);
    void initSocket(int in,int out);
    void transferData();
    void setTitle(QString title){
        this->item->setTitle(title);
    }


public:
    int index;
    QList<Node*> input_nodes;
    QList<Node*> output_nodes;
    int input_vaild = 0;
    int output_vaild = 0;
//    Node* input_node;
//    Node* output_node;

    QList<NodeSocket*> input_sockets;
    QList<NodeSocket*> output_sockets;
    QList<NodeSocket*> connect_sockets;
    int input_socket_number;
    int output_socket_number;

    bool visited = false;
    bool canCompute = true;


    NodeShader* item = nullptr;

};

#endif // NODE_H
