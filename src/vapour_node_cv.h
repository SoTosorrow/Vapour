#ifndef VAPOUR_NODE_CV_H
#define VAPOUR_NODE_CV_H

#include"vapour_node.h"
#include"vapour_descriptor_cv.h"

class VapourNodeCvInput : public VapourNode
{
public:
    VapourNodeCvInput(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour CV-Input";
        initDesc(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorCvInput(input_socket_number,output_socket_number,"Cv-test",2);
        // 节点大小
        this->desc->setTitle("CV-test");
        this->desc->setDescWidth(300);
        this->desc->setDescHeight(180);
    }
    virtual void initData(){
        qDebug()<<"initData";
        //qDeleteAll(input_datas);
        input_datas.clear();
        //qDeleteAll(output_datas);
        output_datas.clear();
        cv::Mat m(2, 2, CV_8UC3, cv::Scalar(0, 0, 255));
        for(int i=0;i<this->desc->input_sockets.length();i++){
            input_datas.append({m});
            input_datas[i].data = this->desc->interaction->edits[i]->text().toDouble();
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append({m});
        }
    }
    virtual void handle(){
        qDebug()<<"handle"<<input_datas.length()<<output_datas.length();
        output_datas[0] = input_datas[0];
//        for(int i=0;i<input_datas.length();i++){
//            this->desc->interaction->edits[i]->setText(QString::number(this->input_datas[i].data));
//        }
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
    //VapourDescriptor* desc;
    QList<DMat> input_datas;
    QList<DMat> output_datas;
};


// D:\Object\CuteCss\1.jpg


#endif // VAPOUR_NODE_CV_H
