#pragma once
#ifndef VSOCKET_H
#define VSOCKET_H

#include<QGraphicsItem>
#include<QColor>
#include<QtGui>
#include<QDebug>
#include<QGraphicsSceneMouseEvent>

#include "types.h"

class VSocket : public QGraphicsItem
{
public:
    VSocket(QGraphicsItem *parent = nullptr);
    VSocket(const VSocket &socket,QGraphicsItem *parent = nullptr);
    void operator=(const VSocket &socket);
    ~VSocket();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect()const override;
    bool contains(const QPointF &point) const override;

    void setIndex(int index)
    {
        this->_index = index;
    }
    int getIndex()
    {
        return this->_index;
    }
    void setConnectType(VSocketConnectType socketConnectType)
    {
        this->_socketConnectType = socketConnectType;
    }
    void setType(VSocketType socketType)
    {
        this->_socketType = socketType;
    }
    void setDataType(VDataType dataType)
    {
        this->_dataType = dataType;
    }
    VDataType getDataType()
    {
        return this->_dataType;
    }
    void setConnectedTrue()
    {
        _isConnected = true;
    }
    void setConnectedFalse()
    {
        _isConnected = false;
    }
    bool getConnectedState(){
        return _isConnected;
    }

private:
    int _index;
    VSocketConnectType _socketConnectType = VSingleSocket;
    VDataType _dataType = VDataTypeDouble;
    VSocketType _socketType;
    bool _isConnected=false;

    float _radius = 6.0;
    QColor _colorBasic;// diff color for sockerUI
    QColor _colorOutline;
    QPen _pen;
    QBrush _brush;
};

#endif // VSOCKET_H
