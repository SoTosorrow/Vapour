#pragma once
#ifndef VDESCRIPTOR_DEVELOP_H
#define VDESCRIPTOR_DEVELOP_H

#include "vdescriptor.h"

class VDescriptorInput : public VDescriptor
{
public:
    VDescriptorInput(int in_num,int out_num,int edit_number=1)
        :VDescriptor(in_num,out_num,edit_number)
    {
        this->interaction = new VActionEdit(edit_number);
        this->interaction->setGeometry(_edgeSize, _titleHeight+0.5*_edgeSize,
                                   _width - 2*_edgeSize,_height - 2*_edgeSize - _titleHeight);
        this->_proxyContent->setWidget(this->interaction);
    }
    QPointF getPos() override{
        return this->pos();
    }
    void setText(int n,QString t) override{
        this->interaction->_edits[n]->setText(t);
    }
    double getText(int n) override{
        qDebug()<<"111"<<this->interaction->_edits[n]->text().toDouble();
        return this->interaction->_edits[n]->text().toDouble();
    }

public:
    VActionEdit* interaction;

};

class VDescriptorOutput : public VDescriptor
{
public:
    VDescriptorOutput(int in_num,int out_num,int edit_number=1)
        :VDescriptor(in_num,out_num,edit_number)
    {
        this->_interaction = new VActionText(edit_number);
        this->_interaction->setGeometry(_edgeSize, _titleHeight+0.5*_edgeSize,
                                   _width - 2*_edgeSize,_height - 2*_edgeSize - _titleHeight);
        this->_proxyContent->setWidget(this->interaction);
    }
    QPointF getPos() override{
        return this->pos();
    }
    void setText(int n,QString t) override{
        this->interaction->_edits[n]->setText(t);
    }
    double getText(int n) override{
        return this->interaction->_edits[n]->text().toDouble();
    }

public:
    VActionText* interaction;

};
#endif // VDESCRIPTOR_DEVELOP_H
