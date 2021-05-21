#ifndef VAPOUR_NODE_DEVELOP_H
#define VAPOUR_NODE_DEVELOP_H

#include"vapour_node.h"

class VapourNodeInput : public VapourNode
{
public:
    VapourNodeInput(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour-node-Input";
        initDesc(2,1);
        // Desc interaction init
        this->desc = new VapourDescriptor(input_socket_number,output_socket_number,"test");
    }
    virtual void initData(){
        qDebug()<<"initData";
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
        qDebug()<<"a";
    }
};








#endif // VAPOUR_NODE_DEVELOP_H
