#pragma once
#ifndef VDESCRIPTOR_CV_H
#define VDESCRIPTOR_CV_H

#include "vaction_cv.h"
#include "vdescriptor.h"

class VDescriptorCvInput : public VDescriptor
{
public:
    VDescriptorCvInput();
    VDescriptorCvInput(int in_num,int out_num,int edit_number=1)
        :VDescriptor(in_num,out_num,edit_number)
    {
        cv::Mat m = cv::imread("C:\\Users\\Cuimi\\Desktop\\111.jpg");
        interaction = new VActionCvInput(edit_number);
        this->interaction->setGeometry(_edgeSize, _titleHeight+0.5*_edgeSize,
                                   _width - 2*_edgeSize,_height - 2*_edgeSize - _titleHeight);
        this->_proxyContent->setWidget(this->interaction);
    }
    QPointF getPos() override{
        return this->pos();
    }
    void setText(int n,QString t) override{
        Q_UNUSED(n);
        Q_UNUSED(t);
        //this->interaction->edits[n]->setText(t);
    }

    QList<QString> getParams() override
    {
        QList<QString> params;
        params.append(this->interaction->edits[0]->text());
        return params;
    }


public:
    VActionCvInput* interaction;

};

class VDescriptorCvStringParams : public VDescriptor
{
public:
    VDescriptorCvStringParams();
    VDescriptorCvStringParams(int in_num,int out_num,int edit_number=1)
        :VDescriptor(in_num,out_num,edit_number)
    {
        this->edit_number = edit_number;
        interaction = new VActionCvStringParams(edit_number);
        this->interaction->setGeometry(_edgeSize, _titleHeight+0.5*_edgeSize,
                                   _width - 2*_edgeSize,_height - 2*_edgeSize - _titleHeight);
        this->_proxyContent->setWidget(this->interaction);
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
    VActionCvStringParams* interaction;
    int edit_number;

};

#endif // VDESCRIPTOR_CV_H
