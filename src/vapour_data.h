#ifndef VAPOURDATA_H
#define VAPOURDATA_H

#include<QDebug>
#include"vapour_types.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/core/core.hpp>

class VapourData
{
public:
    VapourData(){
        this->data_type = VapourDataTypeBasic;
    }
    virtual ~VapourData(){}
    VapourDataType dataType(){
        return this->data_type;
    }


    virtual void setData(double data){
        qDebug()<<typeid(data).name();
    }
    virtual void setData(cv::Mat data){
        qDebug()<<typeid(data).name();
    }
    virtual double getDoubleData(){ return {};}
    virtual cv::Mat getMatData(){ return {};}

public:
    VapourDataType data_type;
};

class VapourDataDouble : public VapourData
{
public:
    VapourDataDouble():VapourData(){
        VapourData::data_type = VapourDataTypeDouble;
        this->data = 0;
    }
    ~VapourDataDouble(){}
    void setData(double data) override{
        this->data = data;
    }
    double getDoubleData() override{
        return this->data;
    }


public:
    double data;
};

class VapourDataMat : public VapourData
{
public:
    VapourDataMat():VapourData(){
        VapourData::data_type = VapourDataTypeMat;
    }
    ~VapourDataMat(){}
    void setData(cv::Mat data) override{
        this->data = data;
    }
    cv::Mat getMatData() override{
        return this->data;
    }

public:
    cv::Mat data;

};

#endif // VAPOURDATA_H
