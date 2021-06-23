#ifndef VAPOUR_NODE_DEVELOP_H
#define VAPOUR_NODE_DEVELOP_H

#include"vapour_node.h"
#include"vapour_edge.h"

class VapourNodeInput : public VapourNode
{
public:
    VapourNodeInput(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour node-Input";
        initDesc(1,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorInput(input_socket_number,output_socket_number,"Input",1);
        // 节点大小
        this->desc->setDescWidth(130);
        this->desc->setDescHeight(80);
        this->setTitle("DoubleInput");
    }
    VapourNodeType getType() override{
        return VapourNodeTypeInput;
    }
    void initData() override{
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->getDesc()->input_sockets.length();i++){
            input_datas.append(new VapourDataDouble());
            input_datas[i]->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->output_sockets.length();i++){
            output_datas.append(new VapourDataDouble());
        }
    }
    void handle() override{
        output_datas[0]->setData(input_datas[0]->getDoubleData());
        for(int i=0;i<input_datas.length();i++){
            this->desc->setText(i,QString::number(this->input_datas[i]->getDoubleData()));
        }
    }
    void transfer() override{
//        for(int i=0;i<this->output_nodes.length();i++){
//            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
//                        this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first]->getDoubleData());

//        }


        //update:check
        for(int i=0;i<this->output_edges.length();i++){
            qDebug()<<this->output_edges[i]->output_node->index<<output_edges[i]->output_socket->index<<
                      output_edges[i]->input_node->index<<output_edges[i]->input_socket->index;
            this->output_edges[i]->output_node->input_datas[output_edges[i]->output_socket->index]->setData(
                        this->output_edges[i]->input_node->output_datas[output_edges[i]->input_socket->index]->getDoubleData());
        }
    }

};

class VapourNodeAdd : public VapourNode
{
public:
    VapourNodeAdd(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour node-Input";
        initDesc(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorInput(input_socket_number,output_socket_number,"Input",2);
        // 节点大小
        this->desc->setDescWidth(160);
        this->desc->setDescHeight(120);
        this->setTitle("DoubleAdd");
    }
    VapourNodeType getType() override{
        return VapourNodeTypeAdd;
    }
    void initData() override{
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->getDesc()->input_sockets.length();i++){
            input_datas.append(new VapourDataDouble());
            input_datas[i]->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->output_sockets.length();i++){
            output_datas.append(new VapourDataDouble());
        }
    }
    void handle() override{
        output_datas[0]->setData(input_datas[0]->getDoubleData() + input_datas[1]->getDoubleData());
        for(int i=0;i<input_datas.length();i++){
            this->desc->setText(i,QString::number(this->input_datas[i]->getDoubleData()));
        }
    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                        this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first]->getDoubleData());
        }
    }

};

class VapourNodeSub : public VapourNode
{
public:
    VapourNodeSub(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour node-Input";
        initDesc(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorInput(input_socket_number,output_socket_number,"Input",2);
        // 节点大小
        this->desc->setDescWidth(160);
        this->desc->setDescHeight(120);
        this->setTitle("DoubleSub");
    }
    VapourNodeType getType() override{
        return VapourNodeTypeSub;
    }
    void initData() override{
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->getDesc()->input_sockets.length();i++){
            input_datas.append(new VapourDataDouble());
            input_datas[i]->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->output_sockets.length();i++){
            output_datas.append(new VapourDataDouble());
        }
    }
    void handle() override{
        output_datas[0]->setData(input_datas[0]->getDoubleData() - input_datas[1]->getDoubleData());
        for(int i=0;i<input_datas.length();i++){
            this->desc->setText(i,QString::number(this->input_datas[i]->getDoubleData()));
        }
    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                        this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first]->getDoubleData());
        }
    }

};

class VapourNodeMul : public VapourNode
{
public:
    VapourNodeMul(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour node-Input";
        initDesc(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorInput(input_socket_number,output_socket_number,"Input",2);
        // 节点大小
        this->desc->setDescWidth(160);
        this->desc->setDescHeight(120);
        this->setTitle("DoubleMul");
    }
    VapourNodeType getType() override{
        return VapourNodeTypeMul;
    }
    void initData() override{
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->getDesc()->input_sockets.length();i++){
            input_datas.append(new VapourDataDouble());
            input_datas[i]->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->output_sockets.length();i++){
            output_datas.append(new VapourDataDouble());
        }
    }
    void handle() override{
        output_datas[0]->setData(input_datas[0]->getDoubleData() * input_datas[1]->getDoubleData());
        for(int i=0;i<input_datas.length();i++){
            this->desc->setText(i,QString::number(this->input_datas[i]->getDoubleData()));
        }
    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                        this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first]->getDoubleData());
        }
    }

};

class VapourNodeDiv : public VapourNode
{
public:
    VapourNodeDiv(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour node-Input";
        initDesc(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorInput(input_socket_number,output_socket_number,"Input",2);
        // 节点大小
        this->desc->setDescWidth(160);
        this->desc->setDescHeight(120);
        this->setTitle("DoubleDiv");
    }
    VapourNodeType getType() override{
        return VapourNodeTypeDiv;
    }
    void initData() override{
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->getDesc()->input_sockets.length();i++){
            input_datas.append(new VapourDataDouble());
            input_datas[i]->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->output_sockets.length();i++){
            output_datas.append(new VapourDataDouble());
        }
    }
    void handle() override{
        output_datas[0]->setData(input_datas[0]->getDoubleData() / input_datas[1]->getDoubleData());
        for(int i=0;i<input_datas.length();i++){
            this->desc->setText(i,QString::number(this->input_datas[i]->getDoubleData()));
        }
    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                        this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first]->getDoubleData());
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
        this->setTitle("DoubleOutput");
    }
    VapourNodeType getType() override{
        return VapourNodeTypeOutput;
    }
    void initData() override{
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->getDesc()->input_sockets.length();i++){
            input_datas.append(new VapourDataDouble());
        }
        for(int i=0;i<this->getDesc()->output_sockets.length();i++){
            output_datas.append(new VapourDataDouble());
        }
    }
    virtual void handle() override{
        for(int i=0;i<input_datas.length();i++){
            this->desc->setText(i,QString::number(this->input_datas[i]->getDoubleData()));
        }
    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            qDebug()<<this->connect_info[i].first.first->index<<this->connect_info[i].first.second->index<<
                      this->connect_info[i].second.first<<this->connect_info[i].second.second;
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                        this->connect_info[i].first.first->output_datas[this->connect_info[i].second.first]->getDoubleData());
        }
    }

};








#endif // VAPOUR_NODE_DEVELOP_H
