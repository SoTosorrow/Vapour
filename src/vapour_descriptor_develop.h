#ifndef VAPOUR_DESCRIPTOR_DEVELOP_H
#define VAPOUR_DESCRIPTOR_DEVELOP_H


#include"vapour_descriptor.h"

class VapourDescriptorInput : public VapourDescriptor
{
public:
    VapourDescriptorInput(int in_num,int out_num,QString node_name,int edit_number=1)
        :VapourDescriptor(in_num,out_num,node_name,edit_number)
    {
        this->interaction = new VapourActionEdit(edit_number);
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
    double getText(int n) override{
        return this->interaction->edits[n]->text().toDouble();
    }

public:
    VapourActionEdit* interaction;

};

class VapourDescriptorOutput : public VapourDescriptor
{
public:
    VapourDescriptorOutput(int in_num,int out_num,QString node_name,int edit_number=1)
        :VapourDescriptor(in_num,out_num,node_name,edit_number)
    {
        this->interaction = new VapourActionText(edit_number);
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
    double getText(int n) override{
        return this->interaction->edits[n]->text().toDouble();
    }

public:
    VapourActionText* interaction;

};

#endif // VAPOUR_DESCRIPTOR_DEVELOP_H
