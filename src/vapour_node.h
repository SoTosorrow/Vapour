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
    virtual void initData(){
        //qDeleteAll(input_datas);
        input_datas.clear();
        //qDeleteAll(output_datas);
        output_datas.clear();
        for(int i=0;i<this->desc->input_sockets.length();i++){
            input_datas.append({0});
            input_datas[i].data = this->desc->interaction->edits[i]->text().toDouble();
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append({0});
        }
    }
    virtual void handle(){
        qDebug()<<"handle"<<input_datas.length()<<output_datas.length();
        output_datas[0] = input_datas[0];

        for(int i=0;i<input_datas.length();i++){
            this->desc->interaction->edits[i]->setText(QString::number(this->input_datas[i].data));
        }
    }
    virtual void transfer(){
        for(int i=0;i<this->output_nodes.length();i++){
            qDebug()<<this->connect_info[i].first.first->index<<this->connect_info[i].first.second->index<<
                      this->connect_info[i].second.first<<this->connect_info[i].second.second;
//            for(int j=0;j<this->input_datas.length();j++)
//                qDebug()<<this->input_datas[j].data;
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]=
                    this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first];
        }
    }


public:
    int index;
    VapourDescriptor* desc;
    //QList<QPair<VapourNode*,QPair<int,int>>> connect_info;
    QList<QPair<QPair<VapourNode*,VapourNode*>,QPair<int,int>>> connect_info;
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
