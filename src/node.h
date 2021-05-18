#pragma once
#ifndef NODE_H
#define NODE_H

#include<QGraphicsScene>
#include<QWidget>
#include<QList>

#include"number/node_item.h"
#include"shader/node_shader.h"
#include"node_socket.h"


class Node : public QWidget
{
public:
    Node(QWidget *parent=nullptr);
    Node(int type, QWidget *parent=nullptr);
    ~Node();

    Node(const Node& node,QWidget *parent=nullptr);
    void operator=(const Node &node);

    void setPos(QPointF pos);
    void setIndex(int index);
    void initSocket(int in,int out);
    void transferData();
    void setTitle(QString title){
        if(node_type==DATA_NUMBER)
            this->item->setTitle(title);
        if(node_type==DATA_SHADER)
            this->shader_item->setTitle(title);
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


    NodeItem* item=nullptr;
    NodeShader* shader_item = nullptr;
    enum DATA_TYPE node_type = DATA_NUMBER;

};

#endif // NODE_H
