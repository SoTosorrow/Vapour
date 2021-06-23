#pragma once
#ifndef VNODE_CV_H
#define VNODE_CV_H

#include "vaction_cv.h"
#include "vdescriptor_cv.h"
#include "vnode.h"
#include "vedge.h"

class VNodeCvInput : public VNode
{
public:
    VNodeCvInput(QWidget *parent=nullptr)
        :VNode(parent)
    {
        qDebug()<<"Create: Vapour CV-Input";
        initSocketNumber(1,1);
        // 定义节点描述，自动定义节点用户接口
        this->setDesc(new VDescriptorCvInput(_inputSocketNumber,_outputSocketNumber,2));
        // 节点大小
        this->getDesc()->setDescWidth(180);
        this->getDesc()->setDescHeight(80);
        // socket type
        this->getDesc()->setSocketDataType(0,0,VDataTypeMat);
        this->getDesc()->setSocketDataType(1,0,VDataTypeMat);
        this->setTitle("ImageInput");
    }
    void initData() override{
        qDeleteAll(_inputDatas);
        _inputDatas.clear();
        qDeleteAll(_outputDatas);
        _outputDatas.clear();
        cv::Mat m;
        for(int i=0;i<this->getDesc()->getInputSocketsLength();i++){
            _inputDatas.append(new VDataMat());
            m = cv::imread(this->getDesc()->getParams()[0].toStdString());
            VDataMat* data = dynamic_cast<VDataMat*>(_inputDatas[i]);
            data->setData(m);
        }
        for(int i=0;i<this->getDesc()->getoutputSocketsLength();i++){
            _outputDatas.append(new VDataMat());
        }
    }
    void handle() override{
        VDataMat* inputData = dynamic_cast<VDataMat*>(_inputDatas[0]);
        VDataMat* outputData = dynamic_cast<VDataMat*>(_outputDatas[0]);
        outputData->setData(inputData->getData());
    }
    void transfer() override{
        for(int i=0;i<this->getOutputNodes().length();i++){
            VDataMat* data = dynamic_cast<VDataMat*>(_outputEdges[i]->getStartNode()->getOutputDatas()[_outputEdges[i]->_startSocket->getIndex()]);
            VDataMat* data2 = dynamic_cast<VDataMat*>(_outputEdges[i]->getEndNode()->getInputDatas()[_outputEdges[i]->_endSocket->getIndex()]);
            data2->setData(data->getData());
        }
        VDataMat* outputData = dynamic_cast<VDataMat*>(_outputDatas[0]);
        cv::imshow("a",outputData->getData());
    }

};

class VNodeCvConvert : public VNode
{
public:
    VNodeCvConvert(QWidget *parent=nullptr)
        :VNode(parent)
    {
        qDebug()<<"Create: Vapour CV-Convert";
        initSocketNumber(2,1);
        // 定义节点描述，自动定义节点用户接口
        this->setDesc(new VDescriptorCvStringParams(_inputSocketNumber,_outputSocketNumber,1));
        // adjust pos to be beautiful
        VDescriptorCvStringParams* desc = dynamic_cast<VDescriptorCvStringParams*>(getDesc());
        desc->interaction->edits[0]->setGeometry(0,1*30,100,25);

        // 节点大小
        this->getDesc()->setDescWidth(180);
        this->getDesc()->setDescHeight(100);
        // socket type
        this->getDesc()->setSocketDataType(0,0,VDataTypeMat);
        this->getDesc()->setSocketDataType(0,1,VDataTypeDouble);
        this->getDesc()->setSocketDataType(1,0,VDataTypeMat);

        this->setTitle("ImageConvert");
    }
    void initData() override{
        qDeleteAll(_inputDatas);
        _inputDatas.clear();
        qDeleteAll(_outputDatas);
        _outputDatas.clear();

        _inputDatas.append(new VDataMat());
        _inputDatas.append(new VDataDouble());

        for(int i=0;i<this->getDesc()->getoutputSocketsLength();i++){
            _outputDatas.append(new VDataMat());
        }
    }
    void handle() override{
        int type;
        cv::Mat m;

        // type socket have connected
        if(this->getDesc()->getInputSockets()[1]->getConnectedState())
        {
            VDataDouble* inputType = dynamic_cast<VDataDouble*>(_inputDatas[1]);
            this->getDesc()->setText(0,QString::number(inputType->getData()));
        }
        type = this->getDesc()->getParams()[0].toInt();

        VDataMat* inputdata = dynamic_cast<VDataMat*>(_inputDatas[0]);
        VDataMat* outputdata = dynamic_cast<VDataMat*>(_outputDatas[0]);
        cvtColor(inputdata->getData(),m,type);
        outputdata->setData(m);
    }
    void transfer() override{
        for(int i=0;i<this->getOutputNodes().length();i++){
            VDataMat* data = dynamic_cast<VDataMat*>(_outputEdges[i]->getStartNode()->getOutputDatas()[_outputEdges[i]->_startSocket->getIndex()]);
            VDataMat* data2 = dynamic_cast<VDataMat*>(_outputEdges[i]->getEndNode()->getInputDatas()[_outputEdges[i]->_endSocket->getIndex()]);
            data2->setData(data->getData());
        }
        VDataMat* outputData = dynamic_cast<VDataMat*>(_outputDatas[0]);
        cv::imshow("a",outputData->getData());
    }

};

class VNodeCvThreshold : public VNode
{
public:
    VNodeCvThreshold(QWidget *parent=nullptr)
        :VNode(parent)
    {
        qDebug()<<"Create: Vapour CV-Threshold";
        initSocketNumber(4,1);
        // 定义节点描述，自动定义节点用户接口
        this->setDesc(new VDescriptorCvStringParams(_inputSocketNumber,_outputSocketNumber,3));
        // 节点大小
        this->getDesc()->setDescWidth(180);
        this->getDesc()->setDescHeight(160);
        // socket type
        this->getDesc()->setSocketDataType(0,0,VDataTypeDouble);
        this->getDesc()->setSocketDataType(0,1,VDataTypeDouble);
        this->getDesc()->setSocketDataType(0,2,VDataTypeDouble);
        this->getDesc()->setSocketDataType(0,3,VDataTypeMat);
        this->getDesc()->setSocketDataType(1,0,VDataTypeMat);
        this->setTitle("ImageThreshold");
    }
    void initData() override{
        qDeleteAll(_inputDatas);
        _inputDatas.clear();
        qDeleteAll(_outputDatas);
        _outputDatas.clear();

        _inputDatas.append(new VDataDouble());
        _inputDatas.append(new VDataDouble());
        _inputDatas.append(new VDataDouble());
        _inputDatas.append(new VDataMat());
        for(int i=0;i<this->getDesc()->getoutputSocketsLength();i++){
            _outputDatas.append(new VDataMat());
        }
    }
    void handle() override{
        double thresh;
        double maxval;
        int type;
        cv::Mat m;

        // type socket have connected
        if(this->getDesc()->getInputSockets()[0]->getConnectedState())
        {
            VDataDouble* inputType = dynamic_cast<VDataDouble*>(_inputDatas[0]);
            this->getDesc()->setText(0,QString::number(inputType->getData()));
        }
        // type socket have connected
        if(this->getDesc()->getInputSockets()[1]->getConnectedState())
        {
            VDataDouble* inputType = dynamic_cast<VDataDouble*>(_inputDatas[1]);
            this->getDesc()->setText(1,QString::number(inputType->getData()));
        }
        // type socket have connected
        if(this->getDesc()->getInputSockets()[2]->getConnectedState())
        {
            VDataDouble* inputType = dynamic_cast<VDataDouble*>(_inputDatas[2]);
            this->getDesc()->setText(2,QString::number(inputType->getData()));
        }

        thresh = this->getDesc()->getParams()[0].toDouble();
        maxval = this->getDesc()->getParams()[1].toDouble();
        type = this->getDesc()->getParams()[2].toInt();
        VDataMat* inputData = dynamic_cast<VDataMat*>(_inputDatas[3]);
        VDataMat* outputData = dynamic_cast<VDataMat*>(_outputDatas[0]);
        cv::threshold(inputData->getData(),m,thresh,maxval,type);
        outputData->setData(m);


        /*
            CV_THRESH_BINARY
            CV_THRESH_BINARY_INV
            CV_THRESH_TRUNC
            CV_THRESH_TOZERO
            CV_THRESH_TOZERO_INV
        */
    }
    void transfer() override{
        for(int i=0;i<this->getOutputNodes().length();i++){
            VDataMat* data = dynamic_cast<VDataMat*>(_outputEdges[i]->getStartNode()->getOutputDatas()[_outputEdges[i]->_startSocket->getIndex()]);
            VDataMat* data2 = dynamic_cast<VDataMat*>(_outputEdges[i]->getEndNode()->getInputDatas()[_outputEdges[i]->_endSocket->getIndex()]);
            data2->setData(data->getData());
        }
        VDataMat* outputData = dynamic_cast<VDataMat*>(_outputDatas[0]);
        cv::imshow("a",outputData->getData());
    }

};


#endif // VNODE_CV_H
