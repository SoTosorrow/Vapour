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
        this->desc->setTitle("CV-test");
        this->desc->setDescWidth(300);
        this->desc->setDescHeight(180);
    }
    void initData() override{
        qDebug()<<"initData";
        //qDeleteAll(input_datas);
        input_datas.clear();
        //qDeleteAll(output_datas);
        output_datas.clear();
        cv::Mat m;
        for(int i=0;i<this->desc->input_sockets.length();i++){
            m = cv::imread(this->getDesc()->getFile().toStdString());
            input_datas.append({m});
            input_datas[i].data = m;
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append({m});
        }
    }
    void handle() override{
        output_datas[0].data = input_datas[0].data;

    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->setInputDatas(this->connect_info[i].second.second,this->connect_info[i].first.first->getOutputDatas()[0]);
        }
        cv::imshow("a",output_datas[0].data);
    }
    QList<DMat> getInputDatas() override{
        return this->input_datas;
    }
    QList<DMat> getOutputDatas() override{
        return this->output_datas;
    }
    void setInputDatas(int n,DMat m) override{
        this->input_datas[n].data = m.data;
    }
    void setOutputDatas(int n,DMat m) override{
        this->output_datas[n].data = m.data;
    }
//     C:\\Users\\Cuimi\\Desktop\\111.jpg
public:
    QList<DMat> input_datas;
    QList<DMat> output_datas;
};

class VapourNodeCvAdd : public VapourNode
{
public:
    VapourNodeCvAdd(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour CV-Input";
        initDesc(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorCvAdd(input_socket_number,output_socket_number,"Cv-test",2);
        // 节点大小
        this->desc->setTitle("CV-test");
        this->desc->setDescWidth(300);
        this->desc->setDescHeight(180);
    }
    void initData() override{
        qDebug()<<"initData";
        //qDeleteAll(input_datas);
        input_datas.clear();
        //qDeleteAll(output_datas);
        output_datas.clear();
        cv::Mat m;
        for(int i=0;i<this->desc->input_sockets.length();i++){
            input_datas.append({m});
        }
        for(int i=0;i<this->desc->output_sockets.length();i++){
            output_datas.append({m});
        }

    }
    void handle() override{
        output_datas[0].data = input_datas[0].data + input_datas[1].data;
        int x,y,w,h;
        x = this->getDesc()->getParams()[0].toInt();
        y = this->getDesc()->getParams()[1].toInt();
        w = this->getDesc()->getParams()[2].toInt();
        h = this->getDesc()->getParams()[3].toInt();
        qDebug()<<x<<y<<w<<h;

        cv::Mat_<cv::Vec3b> im = input_datas[0].data;
        cv::Mat_<cv::Vec3b> im2 = input_datas[1].data;
        qDebug()<<input_datas[0].data.rows<<input_datas[0].data.cols;
        qDebug()<<input_datas[1].data.rows<<input_datas[1].data.cols;
        // 300 900 800 1300
        for (int i = x; i < y; i++) {
            for (int j = w; j < h; j++) {
                im(i, j)[0] = im2(i, j)[0];
                im(i, j)[1] = im2(i, j)[1];
                im(i, j)[2] = im2(i, j)[2];
            }
        }
        output_datas[0].data = im;

    }
    void transfer() override{
        for(int i=0;i<this->output_nodes.length();i++){
            this->connect_info[i].first.second->setInputDatas(this->connect_info[i].second.second,this->connect_info[i].first.first->getOutputDatas()[0]);
        }
        cv::imshow("a",output_datas[0].data);
    }
    QList<DMat> getInputDatas() override{
        return this->input_datas;
    }
    QList<DMat> getOutputDatas() override{
        return this->output_datas;
    }
    void setInputDatas(int n,DMat m) override{
        this->input_datas[n].data = m.data;
    }
    void setOutputDatas(int n,DMat m) override{
        this->output_datas[n].data = m.data;
    }
//     C:\\Users\\Cuimi\\Desktop\\111.jpg
public:
    QList<DMat> input_datas;
    QList<DMat> output_datas;

};


class VapourNodeCvLoad : public VapourNode
{
public:
    VapourNodeCvLoad(QWidget *parent=nullptr):VapourNode(parent){
        qDebug()<<"Create: Vapour CV-Input";
        initDesc(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->desc = new VapourDescriptorCvInput(input_socket_number,output_socket_number,"Cv-test",2);
        // 节点大小
        this->desc->setTitle("CV-test");
        this->desc->setDescWidth(300);
        this->desc->setDescHeight(180);
    }
    void initData() override{
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
    void handle() override{
        qDebug()<<"handle"<<input_datas.length()<<output_datas.length();
        output_datas[0] = input_datas[0];
//        for(int i=0;i<input_datas.length();i++){
//            this->desc->interaction->edits[i]->setText(QString::number(this->input_datas[i].data));
//        }
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

public:
    //VapourDescriptor* desc;
    QList<DMat> input_datas;
    QList<DMat> output_datas;
};




#endif // VAPOUR_NODE_CV_H
