#pragma once
#ifndef TYPES_H
#define TYPES_H

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/core/core.hpp>

enum VNodeType
{
    VNodeTypeBasic = -1,
    VNodeTypeNumber = 1,
    VNodeTypeNumberAdd = 2,
    VNodeTypeNumberSub = 3,
    VNodeTypeNumberMul = 4,
    VNodeTypeNumberDiv = 5,
};

enum VSocketConnectType{
    VSingleSocket = 0,
    // UnionSocket inputs has always append but not have a common number
    VUnionSocket = 1,
};

enum VSocketType{
    VInputSocket = 0,
    VOutputSocket = 1,
};

enum VDataType{
    VDataTypeBasic = -1,
    VDataTypeDouble = 0,
    VDataTypeString = 1,
    VDataTypeMat = 2,
};

struct Connect{
    // for a node
    int input_index=-1;
    int output_index=-1;

    bool operator==(const Connect c){
        return (input_index==c.input_index && output_index==c.output_index);
    }

};

struct DNumber{
    double data;
};

struct DMat{
    cv::Mat data;
};


#endif // TYPES_H
