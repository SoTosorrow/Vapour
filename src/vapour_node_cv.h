#ifndef VAPOUR_NODE_CV_H
#define VAPOUR_NODE_CV_H

#include"vapour_node.h"
#include"vapour_descriptor_cv.h"

class VapourNodeCvInput : public VapourNode
{
public:
    VapourNodeCvInput(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour CV-Input";
        initDesc(1,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorCvInput(input_socket_number,output_socket_number,"Cv-test",2);
        // 节点大小
        //this->desc->setTitle("CV-test");
        this->desc->setDescWidth(300);
        this->desc->setDescHeight(180);
        this->setTitle("ImageInput");
    }
    void initData() override{
        qDebug()<<"initData";
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();
        cv::Mat m;
        for(int i=0;i<this->desc->input_sockets.length();i++){
            m = cv::imread(this->getDesc()->getFile().toStdString());
            input_datas.append(new VapourDataMat);
            input_datas[i]->setData(m);
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append(new VapourDataMat);
        }
    }
    void handle() override{
        output_datas[0]->setData(input_datas[0]->getMatData());
    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                                                              this->connect_info[i].first.first->output_datas[0]->getMatData());
            cv::imshow("a",output_datas[0]->getMatData());
        }
        cv::imshow("a",output_datas[0]->getMatData());
    }

};

class VapourNodeCvAdd : public VapourNode
{
public:
    VapourNodeCvAdd(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour CV-Input";
        initDesc(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorCvStringParams(input_socket_number,output_socket_number,"Cv-test",4);
        // 节点大小
        //this->desc->setTitle("CV-test");
        this->desc->setDescWidth(300);
        this->desc->setDescHeight(180);
        this->setTitle("ImageAdd");
    }
    void initData() override{
        qDebug()<<"initData";
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();
        cv::Mat m;
        for(int i=0;i<this->desc->input_sockets.length();i++){
            input_datas.append(new VapourDataMat);
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append(new VapourDataMat);
        }

    }
    void handle() override{
        int x,y,w,h;
        x = this->getDesc()->getParams()[0].toInt();
        y = this->getDesc()->getParams()[1].toInt();
        w = this->getDesc()->getParams()[2].toInt();
        h = this->getDesc()->getParams()[3].toInt();

        cv::Mat_<cv::Vec3b> im = input_datas[0]->getMatData();
        cv::Mat_<cv::Vec3b> im2 = input_datas[1]->getMatData();
        qDebug()<<input_datas[0]->getMatData().rows<<input_datas[0]->getMatData().cols;
        qDebug()<<input_datas[1]->getMatData().rows<<input_datas[1]->getMatData().cols;
        for (int i = x; i < y; i++) {
            for (int j = w; j < h; j++) {
                im(i, j)[0] = im2(i, j)[0];
                im(i, j)[1] = im2(i, j)[1];
                im(i, j)[2] = im2(i, j)[2];
            }
        }
        output_datas[0]->setData(im);

    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                                                              this->connect_info[i].first.first->output_datas[0]->getMatData());
            }
        cv::imshow("a",output_datas[0]->getMatData());
    }

};

class VapourNodeCvConvert : public VapourNode
{
public:
    VapourNodeCvConvert(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour CV-Input";
        initDesc(1,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorCvStringParams(input_socket_number,output_socket_number,"Cv-test",1);
        // 节点大小
        //this->desc->setTitle("ImageThreshold");
        this->desc->setDescWidth(300);
        this->desc->setDescHeight(180);
        this->setTitle("ImageConvert");
        this->getDesc()->setText(0,"6");
    }
    void initData() override{
        qDebug()<<"initData";
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->desc->input_sockets.length();i++){
            input_datas.append(new VapourDataMat);
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append(new VapourDataMat);
        }

    }
    void handle() override{
        int type;
        cv::Mat m;
        type = this->getDesc()->getParams()[0].toInt();
        cvtColor(input_datas[0]->getMatData(),m,type);
        output_datas[0]->setData(m);


        /*
            cv::COLOR_BGR2BGRA = 0,
            cv::COLOR_BGR2GRAY = 6,
            CV_THRESH_TOZERO_INV
        */

    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                                                              this->connect_info[i].first.first->output_datas[0]->getMatData());
            }
        cv::imshow("a",output_datas[0]->getMatData());
    }

};

class VapourNodeCvThreshold : public VapourNode
{
public:
    VapourNodeCvThreshold(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour CV-Input";
        initDesc(1,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorCvStringParams(input_socket_number,output_socket_number,"Cv-test",3);
        // 节点大小
        //this->desc->setTitle("ImageThreshold");
        this->desc->setDescWidth(300);
        this->desc->setDescHeight(180);
        this->setTitle("ImageThreshold");
    }
    void initData() override{
        qDebug()<<"initData";
        qDeleteAll(input_datas);
        input_datas.clear();
        qDeleteAll(output_datas);
        output_datas.clear();

        for(int i=0;i<this->desc->input_sockets.length();i++){
            input_datas.append(new VapourDataMat);
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append(new VapourDataMat);
        }

    }
    void handle() override{
        double thresh;
        double maxval;
        int type;
        cv::Mat m;
        thresh = this->getDesc()->getParams()[0].toDouble();
        maxval = this->getDesc()->getParams()[1].toDouble();
        type = this->getDesc()->getParams()[2].toInt();
        cv::threshold(input_datas[0]->getMatData(),m,thresh,maxval,type);
        output_datas[0]->setData(m);


        /*
            CV_THRESH_BINARY
            CV_THRESH_BINARY_INV
            CV_THRESH_TRUNC
            CV_THRESH_TOZERO
            CV_THRESH_TOZERO_INV
        */

    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->input_datas[this->connect_info[i].second.second]->setData(
                                                              this->connect_info[i].first.first->output_datas[0]->getMatData());
            }
        cv::imshow("a",output_datas[0]->getMatData());
    }

};

#endif // VAPOUR_NODE_CV_H
