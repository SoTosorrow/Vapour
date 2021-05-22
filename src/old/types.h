#ifndef TYPES_H
#define TYPES_H

#include<QGraphicsItem>
#include<QString>

const int NumberNodeStart = QGraphicsItem::UserType + 11;
const int NumberNodeCount = 10;

enum SOCKET_TYPE{
    SOCKET_INPUT = 0,
    SOCKET_OUTPUT = 1
};

enum ItemType{
    Type_NodeSocket = QGraphicsItem::UserType + 2,
    Type_NodeEdge = QGraphicsItem::UserType + 3,


    Type_NodeItem = NumberNodeStart -1,
    Type_NodeItemNumber = NumberNodeStart,
    Type_NodeItemAdd = NumberNodeStart + 1,
    Type_NodeItemSub = NumberNodeStart + 2,
    Type_NodeItemMul = NumberNodeStart + 3,
    Type_NodeItemDiv = NumberNodeStart + 4,
    Type_NodeItemOutput = NumberNodeStart + 5,

};

struct NumberData{
    double number;
};

struct ShaderData{
    /*
    QString define=" precision mediump float; \n\
                    uniform vec2 u_resolution; \n\
                    varying vec4 v_Color; \n\
                    uniform float u_time; \n";
    QString customDefine;
    QString customFunc;
    QString head = "void main() { \n";
    QString customCode;
    QString customColor;
    QString end = "\n}";
    */
    QString data;
};


#endif // TYPES_H
