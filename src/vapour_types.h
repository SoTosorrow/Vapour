#ifndef VAPOUR_TYPES_H
#define VAPOUR_TYPES_H

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/core/core.hpp>

enum VapourSocketConnectType{
    VapourSingleSocket = 0,
    // UnionSocket inputs has always append but not have a common number
    VapourUnionSocket = 1,
};

enum VapourSocketType{
    VapourInputSocket = 0,
    VapourOutputSocket = 1,
};

enum VapourSocketDataType{

};


enum VapourDataType{
    VapourDataTypeDouble = 0,
    VapourDataTypeString = 1,
};

struct Connect{
    // for a node
    int input_index=-1;
    int output_index=-1;

    bool operator==(const Connect c){
        return (input_index==c.input_index && output_index==c.output_index);
    }

};

struct Ddata{
    double data;
};

struct DMat{
    cv::Mat data;
};

#endif // VAPOUR_TYPES_H
