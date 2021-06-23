#pragma once
#ifndef VDATA_H
#define VDATA_H

#include <QDebug>
#include "types.h"

class VData
{
public:
    VData()
    {
        this->dataType = VDataTypeBasic;
    }
    virtual ~VData(){}
    VDataType getDataType()
    {
        return this->dataType;
    }


protected:
    VDataType dataType;
};


class VDataDouble : public VData
{
public:
    VDataDouble():VData()
    {
        VData::dataType = VDataTypeDouble;
        this->data = 0;
    }
    ~VDataDouble(){}
    void setData(double data)
    {
        this->data = data;
    }
    double getData()
    {
        return this->data;
    }


public:
    double data;

};

class VDataMat : public VData
{
public:
    VDataMat():VData()
    {
        VData::dataType = VDataTypeMat;
        this->data = 0;
    }
    ~VDataMat(){}
    void setData(cv::Mat data)
    {
        this->data = data;
    }
    cv::Mat getData()
    {
        return this->data;
    }
public:
    cv::Mat data;

};

#endif // VDATA_H
