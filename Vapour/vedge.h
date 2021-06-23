#pragma once
#ifndef VEDGE_H
#define VEDGE_H

#include<QGraphicsPathItem>
#include<QPen>
#include<QPainterPath>
#include<QPainter>

#include "vsocket.h"
#include "vdescriptor.h"

class VNode;
class VEdge : public QGraphicsPathItem
{
public:
    VEdge()=default;
    VEdge(VNode* startNode,
          VNode* endNode,
          VSocket* startSocket,
          VSocket* endSocket,
          QGraphicsItem *parent = nullptr);
    VEdge(const VEdge& edge);
    void operator=(const VEdge &edge);
    ~VEdge();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

    void setIndex(int index)
    {
        this->_index = index;
    }
    int getIndex()
    {
        return this->_index;
    }
    void setStartPos(VSocket *socket)
    {
        this->_startPos = socket->pos();
    }
    void setEndPos(VSocket *socket)
    {
        this->_endPos = socket->pos();
    }
    VNode* getStartNode()
    {
        return this->_startNode;
    }
    VNode* getEndNode()
    {
        return this->_endNode;
    }
    VSocket* getStartSocket()
    {
        return this->_startSocket;
    }
    VSocket* getEndSocket()
    {
        return this->_endSocket;
    }

public:
    int _index;
    VNode* _startNode;
    VNode* _endNode;
    VSocket* _startSocket;
    VSocket* _endSocket;

    QPainterPath _path;
    QPointF _startPos;
    QPointF _endPos;
    QPointF _startSocketPos;
    QPointF _endSocketPos;


};

#endif // VEDGE_H
