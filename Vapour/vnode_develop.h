#pragma once
#ifndef VNODE_DEVELOP_H
#define VNODE_DEVELOP_H

#include "vnode.h"
#include "vdata.h"
#include "vedge.h"
#include "vdescriptor_develop.h"

class VNodeNumber : public VNode
{
public:
    VNodeNumber(QWidget *parent=nullptr):VNode(parent)
    {
        qDebug()<<"Create: Vapour Node Number";
        initSocketNumber(1,1);
        // 定义节点描述，自动定义节点用户接口
        this->setDesc(new VDescriptorInput(_inputSocketNumber,_outputSocketNumber,1));
        // 节点大小
        this->getDesc()->setDescWidth(150);
        this->getDesc()->setDescHeight(80);
        for(auto i:this->getDesc()->getInputSockets()){
            i->setDataType(VDataTypeDouble);
        }
        for(auto i:this->getDesc()->getOutputSockets()){
            i->setDataType(VDataTypeDouble);
        }
        this->setTitle("DoubleInput");
    }
    VNodeType getType() override{
        return VNodeTypeNumber;
    }
    void initData() override{
        qDeleteAll(_inputDatas);
        _inputDatas.clear();
        qDeleteAll(_outputDatas);
        _outputDatas.clear();

        for(int i=0;i<this->getDesc()->getInputSocketsLength();i++){
            _inputDatas.append(new VDataDouble());
            VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[i]);
            inputData->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->getoutputSocketsLength();i++){
            _outputDatas.append(new VDataDouble());
        }
    }
    void handle() override{
        VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[0]);
        VDataDouble* outputData = static_cast<VDataDouble*>(_outputDatas[0]);

        outputData->setData(inputData->getData());
        this->getDesc()->setText(0,QString::number(inputData->getData()));
    }
    void transfer() override{
        for(int i=0;i<this->_outputEdges.length();i++){
            VDataDouble* data = static_cast<VDataDouble*>(_outputEdges[i]->getStartNode()->getOutputDatas()[_outputEdges[i]->_startSocket->getIndex()]);
            VDataDouble* data2 = static_cast<VDataDouble*>( _outputEdges[i]->getEndNode()->getInputDatas()[_outputEdges[i]->_endSocket->getIndex()]);
            data2->setData(data->getData());
        }
    }
};

class VNodeNumberAdd : public VNode
{
public:
    VNodeNumberAdd(QWidget *parent=nullptr):VNode(parent)
    {
        qDebug()<<"Create: Vapour Node Add";
        initSocketNumber(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->setDesc(new VDescriptorInput(_inputSocketNumber,_outputSocketNumber,2));
        // 节点大小
        this->getDesc()->setDescWidth(180);
        this->getDesc()->setDescHeight(120);
        this->setTitle("DoubleAdd");
    }
    VNodeType getType() override{
        return VNodeTypeNumber;
    }
    void initData() override{
        qDeleteAll(_inputDatas);
        _inputDatas.clear();
        qDeleteAll(_outputDatas);
        _outputDatas.clear();

        for(int i=0;i<this->getDesc()->getInputSocketsLength();i++){
            _inputDatas.append(new VDataDouble());
            VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[i]);
            inputData->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->getoutputSocketsLength();i++){
            _outputDatas.append(new VDataDouble());
        }

    }
    void handle() override{
        VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[0]);
        VDataDouble* inputData2 = static_cast<VDataDouble*>(_inputDatas[1]);
        VDataDouble* outputData = static_cast<VDataDouble*>(_outputDatas[0]);

        outputData->setData(inputData->getData()+inputData2->getData());
        this->getDesc()->setText(0,QString::number(inputData->getData()));
        this->getDesc()->setText(1,QString::number(inputData2->getData()));
    }
    void transfer() override{
        for(int i=0;i<this->_outputEdges.length();i++){
            VDataDouble* data = static_cast<VDataDouble*>(_outputEdges[i]->getStartNode()->getOutputDatas()[_outputEdges[i]->_startSocket->getIndex()]);
            VDataDouble* data2 = static_cast<VDataDouble*>( _outputEdges[i]->getEndNode()->getInputDatas()[_outputEdges[i]->_endSocket->getIndex()]);
            data2->setData(data->getData());
        }
    }
};

class VNodeNumberSub : public VNode
{
public:
    VNodeNumberSub(QWidget *parent=nullptr):VNode(parent)
    {
        qDebug()<<"Create: Vapour Node Sub";
        initSocketNumber(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->setDesc(new VDescriptorInput(_inputSocketNumber,_outputSocketNumber,2));
        // 节点大小
        this->getDesc()->setDescWidth(180);
        this->getDesc()->setDescHeight(120);
        this->setTitle("DoubleSub");
    }
    VNodeType getType() override{
        return VNodeTypeNumber;
    }
    void initData() override{
        qDeleteAll(_inputDatas);
        _inputDatas.clear();
        qDeleteAll(_outputDatas);
        _outputDatas.clear();

        for(int i=0;i<this->getDesc()->getInputSocketsLength();i++){
            _inputDatas.append(new VDataDouble());
            VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[i]);
            inputData->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->getoutputSocketsLength();i++){
            _outputDatas.append(new VDataDouble());
        }
    }
    void handle() override{
        VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[0]);
        VDataDouble* inputData2 = static_cast<VDataDouble*>(_inputDatas[1]);
        VDataDouble* outputData = static_cast<VDataDouble*>(_outputDatas[0]);

        outputData->setData(inputData->getData()-inputData2->getData());
        this->getDesc()->setText(0,QString::number(inputData->getData()));
        this->getDesc()->setText(1,QString::number(inputData2->getData()));
    }
    void transfer() override{
        for(int i=0;i<this->_outputEdges.length();i++){
            VDataDouble* data = static_cast<VDataDouble*>(_outputEdges[i]->getStartNode()->getOutputDatas()[_outputEdges[i]->_startSocket->getIndex()]);
            VDataDouble* data2 = static_cast<VDataDouble*>( _outputEdges[i]->getEndNode()->getInputDatas()[_outputEdges[i]->_endSocket->getIndex()]);
            data2->setData(data->getData());
        }
    }
};

class VNodeNumberMul : public VNode
{
public:
    VNodeNumberMul(QWidget *parent=nullptr):VNode(parent)
    {
        qDebug()<<"Create: Vapour Node Mul";
        initSocketNumber(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->setDesc(new VDescriptorInput(_inputSocketNumber,_outputSocketNumber,2));
        // 节点大小
        this->getDesc()->setDescWidth(180);
        this->getDesc()->setDescHeight(120);
        this->setTitle("DoubleMul");
    }
    VNodeType getType() override{
        return VNodeTypeNumber;
    }
    void initData() override{
        qDeleteAll(_inputDatas);
        _inputDatas.clear();
        qDeleteAll(_outputDatas);
        _outputDatas.clear();

        for(int i=0;i<this->getDesc()->getInputSocketsLength();i++){
            _inputDatas.append(new VDataDouble());
            VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[i]);
            inputData->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->getoutputSocketsLength();i++){
            _outputDatas.append(new VDataDouble());
        }
    }
    void handle() override{
        VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[0]);
        VDataDouble* inputData2 = static_cast<VDataDouble*>(_inputDatas[1]);
        VDataDouble* outputData = static_cast<VDataDouble*>(_outputDatas[0]);

        outputData->setData(inputData->getData()*inputData2->getData());
        this->getDesc()->setText(0,QString::number(inputData->getData()));
        this->getDesc()->setText(1,QString::number(inputData2->getData()));
    }
    void transfer() override{
        for(int i=0;i<this->_outputEdges.length();i++){
            VDataDouble* data = static_cast<VDataDouble*>(_outputEdges[i]->getStartNode()->getOutputDatas()[_outputEdges[i]->_startSocket->getIndex()]);
            VDataDouble* data2 = static_cast<VDataDouble*>( _outputEdges[i]->getEndNode()->getInputDatas()[_outputEdges[i]->_endSocket->getIndex()]);
            data2->setData(data->getData());
        }
    }
};

class VNodeNumberDiv : public VNode
{
public:
    VNodeNumberDiv(QWidget *parent=nullptr):VNode(parent)
    {
        qDebug()<<"Create: Vapour Node Div";
        initSocketNumber(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->setDesc(new VDescriptorInput(_inputSocketNumber,_outputSocketNumber,2));
        // 节点大小
        this->getDesc()->setDescWidth(180);
        this->getDesc()->setDescHeight(120);
        this->setTitle("DoubleDiv");
    }
    VNodeType getType() override{
        return VNodeTypeNumber;
    }
    void initData() override{
        qDeleteAll(_inputDatas);
        _inputDatas.clear();
        qDeleteAll(_outputDatas);
        _outputDatas.clear();

        for(int i=0;i<this->getDesc()->getInputSocketsLength();i++){
            _inputDatas.append(new VDataDouble());
            VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[i]);
            inputData->setData(this->getDesc()->getText(i));
        }
        for(int i=0;i<this->getDesc()->getoutputSocketsLength();i++){
            _outputDatas.append(new VDataDouble());
        }
    }
    void handle() override{
        VDataDouble* inputData = static_cast<VDataDouble*>(_inputDatas[0]);
        VDataDouble* inputData2 = static_cast<VDataDouble*>(_inputDatas[1]);
        VDataDouble* outputData = static_cast<VDataDouble*>(_outputDatas[0]);

        outputData->setData(inputData->getData()/inputData2->getData());
        this->getDesc()->setText(0,QString::number(inputData->getData()));
        this->getDesc()->setText(1,QString::number(inputData2->getData()));
    }
    void transfer() override{
        for(int i=0;i<this->_outputEdges.length();i++){
            VDataDouble* data = static_cast<VDataDouble*>(_outputEdges[i]->getStartNode()->getOutputDatas()[_outputEdges[i]->_startSocket->getIndex()]);
            VDataDouble* data2 = static_cast<VDataDouble*>( _outputEdges[i]->getEndNode()->getInputDatas()[_outputEdges[i]->_endSocket->getIndex()]);
            data2->setData(data->getData());
        }
    }
};

#endif // VNODE_DEVELOP_H
