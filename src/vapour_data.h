#ifndef VAPOURDATA_H
#define VAPOURDATA_H

#include"vapour_types.h"

class VapourData
{
public:
    VapourData(){}

    VapourDataType dataType(){
        return this->data_type;
    }

public:
    VapourDataType data_type;
};

class VapourDataDouble : public VapourData
{
public:
    VapourDataDouble():VapourData(){
        VapourData::data_type = VapourDataTypeDouble;

    }


public:
    double data;
};

#endif // VAPOURDATA_H
