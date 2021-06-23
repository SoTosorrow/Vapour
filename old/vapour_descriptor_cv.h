#ifndef VAPOUR_DESCRIPTOR_CV_H
#define VAPOUR_DESCRIPTOR_CV_H

#include"vapour_descriptor.h"
#include"vapour_action_cv.h"

class VapourDescriptorCvInput : public VapourDescriptor
{
public:
    VapourDescriptorCvInput();
    VapourDescriptorCvInput(int in_num,int out_num,QString node_name,int edit_number=1)
        :VapourDescriptor(in_num,out_num,node_name,edit_number){
        // cv::Mat m(250, 250, CV_8UC3, cv::Scalar(255, 255, 255));
        cv::Mat m = cv::imread("C:\\Users\\Cuimi\\Desktop\\111.jpg");
        interaction = new VapourActionCvInput(m,edit_number);
        this->interaction->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        this->proxyContent->setWidget(this->interaction);
    }
    QPointF getPos() override{
        return this->pos();
    }
    void setText(int n,QString t) override{
        Q_UNUSED(n);
        Q_UNUSED(t);
        //this->interaction->edits[n]->setText(t);
    }
    QString getFile() override{
        return this->interaction->edits[0]->text();
    }
    void test_T_image(cv::Mat m) override{
        this->interaction->tm = m;
    }


public:
    //VapourActionCvShow* interaction;
    VapourActionCvInput* interaction;

};

class VapourDescriptorCvAdd : public VapourDescriptor
{
public:
    VapourDescriptorCvAdd();
    VapourDescriptorCvAdd(int in_num,int out_num,QString node_name,int edit_number=1)
        :VapourDescriptor(in_num,out_num,node_name,edit_number){
        // cv::Mat m(250, 250, CV_8UC3, cv::Scalar(255, 255, 255));
        cv::Mat m = cv::imread("C:\\Users\\Cuimi\\Desktop\\111.jpg");
        interaction = new VapourActionCvShow(m,edit_number);
        this->interaction->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        this->proxyContent->setWidget(this->interaction);
    }
    QPointF getPos() override{
        return this->pos();
    }
    void setText(int n,QString t) override{
        Q_UNUSED(n);
        Q_UNUSED(t);
        //this->interaction->edits[n]->setText(t);
    }
    void test_T_image(cv::Mat m) override{
        this->interaction->tm = m;
    }
    QList<QString> getParams() override{
        QList<QString> a;
        a.append(this->interaction->edits[0]->text());
        a.append(this->interaction->edits[1]->text());
        a.append(this->interaction->edits[2]->text());
        a.append(this->interaction->edits[3]->text());
        return a;
    }


public:
    VapourActionCvShow* interaction;

};

class VapourDescriptorCvStringParams : public VapourDescriptor
{
public:
    VapourDescriptorCvStringParams();
    VapourDescriptorCvStringParams(int in_num,int out_num,QString node_name,int edit_number=1)
        :VapourDescriptor(in_num,out_num,node_name,edit_number){
        this->edit_number = edit_number;
        interaction = new VapourActionCvStringParams(edit_number);
        this->interaction->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        this->proxyContent->setWidget(this->interaction);
    }
    QPointF getPos() override{
        return this->pos();
    }
    void setText(int n,QString t) override{
        this->interaction->edits[n]->setText(t);
    }
    QList<QString> getParams() override{
        QList<QString> a;
        for(int i=0;i<edit_number;i++){
            a.append(this->interaction->edits[i]->text());
        }
        return a;
    }


public:
    VapourActionCvStringParams* interaction;
    int edit_number;

};

#endif // VAPOUR_DESCRIPTOR_CV_H
