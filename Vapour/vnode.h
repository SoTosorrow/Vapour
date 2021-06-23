#pragma once
#ifndef VNODE_H
#define VNODE_H

/*
    @author:Sotosorrow
    @at:2021-6-22

*/
#include<QGraphicsScene>
#include<QWidget>
#include<QList>
#include<utility>
// #include<QPair>

#include "types.h"
#include "vdescriptor.h"
#include "vdata.h"
#include "vdescriptor_develop.h"


class VEdge;
class VNode : public QWidget
{
public:
    VNode(QWidget *parent=nullptr);
    VNode(const VNode &node,QWidget *parent=nullptr);
    virtual ~VNode();
    void operator=(const VNode &node);

    void setIndex(int index)
    {
        this->_index = index;
    }
    int getIndex()
    {
        return this->_index;
    }
    void initSocketNumber(int inputSocketNumber,int outputSocketNumber);
    void setPos(QPointF pos);
    QPointF getPos();
    void setTitle(QString title);
    void setDesc(VDescriptor* desc);
    virtual VDescriptor* getDesc();

    void addInputNode(VNode* node);
    void addOutputNode(VNode* node);
    void addInputEdge(VEdge* edge);
    void addOutputEdge(VEdge* edge);
    void delInputNode(VNode* node);
    void delOutputNode(VNode* node);
    void delInputEdge(VEdge* edge);
    void delOutputEdge(VEdge* edge);
    QList<VData*> getInputDatas()
    {
        return this->_inputDatas;
    }
    QList<VData*> getOutputDatas()
    {
        return this->_outputDatas;
    }
    QList<VEdge*> getInputEdges()
    {
        return this->_inputEdges;
    }
    QList<VEdge*> getOutputEdges()
    {
        return this->_outputEdges;
    }
    QList<VNode*> getInputNodes()
    {
        return this->_inputNodes;
    }
    QList<VNode*> getOutputNodes()
    {
        return this->_outputNodes;
    }

    int getInputSocketNumber()
    {
        return this->_inputSocketNumber;
    }
    int getOutputSocketNumber()
    {
        return this->_outputSocketNumber;
    }


    virtual void setInputData(int index,VData* data);
    virtual VNodeType getType();
    virtual void initData(){}
    virtual void handle(){}
    virtual void transfer(){}

    int inputVaild = 0;
protected:
    VDescriptor* _desc;

    QList<VNode*> _inputNodes;
    QList<VNode*> _outputNodes;

    QList<VEdge*> _inputEdges;
    QList<VEdge*> _outputEdges;

    QList<VData*> _inputDatas;
    QList<VData*> _outputDatas;
//    QList<VDataType> _inputDataTypes;
//    QList<VDataType> _outputDataTypes;

    int _index;
    bool _canCompute = false;
    int _inputSocketNumber;
    int _outputSocketNumber;

//    int _outputVaild = 0;
//    bool visited = false;


};


#endif // VNODE_H
