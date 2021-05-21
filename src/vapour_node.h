#pragma once
#ifndef VAPOURNODE_H
#define VAPOURNODE_H

#include<QGraphicsScene>
#include<QWidget>
#include<QList>
#include<QPair>
#include<utility>
#include"vapour_types.h"
#include"vapour_descriptor.h"
#include"vapour_action_develop.h"

// 释放 connect_info 内存
class VapourNode : public QWidget
{
public:
    VapourNode(QWidget *parent=nullptr);
    VapourNode(const VapourNode& node,QWidget *parent=nullptr);
    void operator=(const VapourNode &node);
    ~VapourNode();

    virtual void handle(){}
    virtual void transfer(){}

    void setPos(QPointF pos){
        this->desc->setPos(pos);
    }
    void setIndex(int index){
        this->index = index;
    }
    void setTitle(QString title){
        this->desc->setTitle(title);
    }
    void initDesc(int in, int out){
        this->input_socket_number = in;
        this->output_socket_number = out;
    }



public:
    int index;
    VapourDescriptor* desc;
    QList<QPair<VapourNode*,QPair<int,int>>> connect_info;
    QList<VapourNode*> input_nodes;
    QList<VapourNode*> output_nodes;
    // input_Data
    // output_Data
    QList<Ddata> input_datas;
    QList<Ddata> output_datas;
    int input_vaild = 0;
    int output_vaild = 0;

    int input_socket_number;
    int output_socket_number;
    bool visited = false;
    bool canCompute = true;


};

#endif // VAPOURNODE_H
