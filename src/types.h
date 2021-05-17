#ifndef TYPES_H
#define TYPES_H

#include<QGraphicsItem>

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


#endif // TYPES_H
