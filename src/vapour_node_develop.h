#ifndef VAPOUR_NODE_DEVELOP_H
#define VAPOUR_NODE_DEVELOP_H

#include"vapour_node.h"

class VapourNodeInput : public VapourNode
{
public:
    VapourNodeInput(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour node-Input";
        initDesc(2,2);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorInput(input_socket_number,output_socket_number,"Input",2);
        // 节点大小
        this->desc->setDescWidth(160);
        this->desc->setDescHeight(120);
    }
    void initData() override{
        //qDeleteAll(input_datas);
        input_datas.clear();
        //qDeleteAll(output_datas);
        output_datas.clear();
        for(int i=0;i<this->desc->input_sockets.length();i++){
            input_datas.append({0});
            input_datas[i].data = this->desc->getText(i);
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append({0});
        }
    }
    void handle() override{
        output_datas[0] = input_datas[0];
        output_datas[1] = input_datas[1];
        for(int i=0;i<input_datas.length();i++){
            this->desc->setText(i,QString::number(this->input_datas[i].data));
        }
    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            qDebug()<<this->connect_info[i].first.first->index<<this->connect_info[i].first.second->index<<
                      this->connect_info[i].second.first<<this->connect_info[i].second.second;
//            for(int j=0;j<this->input_datas.length();j++)
//                qDebug()<<this->input_datas[j].data;
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]=
                    this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first];
        }
    }

};

class VapourNodeOutput : public VapourNode
{
public:
    VapourNodeOutput(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour node-Input";
        initDesc(1,0);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorOutput(input_socket_number,output_socket_number,"Output",1);
        // 节点大小
        this->desc->setDescWidth(200);
        this->desc->setDescHeight(80);
    }
    void initData() override{
        //qDeleteAll(input_datas);
        input_datas.clear();
        //qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->desc->input_sockets.length();i++){
            input_datas.append({0});
            input_datas[i].data = this->desc->getText(i);
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append({0});
        }
    }
    virtual void handle() override{
        // show number
        for(int i=0;i<input_datas.length();i++){
            this->desc->setText(i,QString::number(this->input_datas[i].data));
        }
    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            qDebug()<<this->connect_info[i].first.first->index<<this->connect_info[i].first.second->index<<
                      this->connect_info[i].second.first<<this->connect_info[i].second.second;
//            for(int j=0;j<this->input_datas.length();j++)
//                qDebug()<<this->input_datas[j].data;
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]=
                    this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first];
        }
    }

};








#endif // VAPOUR_NODE_DEVELOP_H
