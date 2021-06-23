#pragma once
#ifndef VDESCRIPTOR_H
#define VDESCRIPTOR_H

#include<QGraphicsItem>
#include<QGraphicsTextItem>
#include<QGraphicsProxyWidget>
#include<QtGui>
#include<QList>

#include "vsocket.h"
#include "vaction.h"
#include "vaction_develop.h"

class VDescriptor : public QGraphicsItem
{
public:
    VDescriptor();
    VDescriptor(int inputNumber,int outputNumber,int editNumber=1);
    VDescriptor(const VDescriptor &desc);
    void operator=(const VDescriptor &desc);
    virtual ~VDescriptor();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    bool contains(const QPointF &point) const override;

    void setSocketNumber(int inputSocketNumber,int outputSocketNumber)
    {
        this->_inputSocketNumber = inputSocketNumber;
        this->_outputSocketNumber = outputSocketNumber;
    }
    void initSocket();
    void setTitle(QString title)
    {
        this->_text->setPlainText(title);
    }
    void setDescWidth(float w)
    {
        this->_width = w;
        for(int i=0;i<_outputSocketNumber;i++)
        {
            _outputSockets[i]->setPos(_width, i*20+34);
        }
    }
    void setDescHeight(float h)
    {
        this->_height = h;
    }
//    void setShape();

    virtual QPointF getPos()
    {
        return this->pos();
    }
    virtual void setText(int n,QString t)
    {
//        qDebug()<<"descriptor"<<n<<t;
//        this->_interaction->edits[n]->setText(t);
        Q_UNUSED(n);
        Q_UNUSED(t);
    }
    virtual double getText(int n){
//        qDebug()<<"descriptor"<<n;
        Q_UNUSED(n);
        return 0;
    }
    virtual QList<QString> getParams()
    {
        return {};
    }
    int getInputSocketNumber()
    {
        return this->_inputSocketNumber;
    }
    int getoutputSocketNumber()
    {
        return this->_outputSocketNumber;
    }
    int getInputSocketsLength()
    {
        return this->_inputSockets.length();
    }
    int getoutputSocketsLength()
    {
        return this->_outputSockets.length();
    }
    QList<VSocket*> getInputSockets()
    {
        return this->_inputSockets;
    }
    QList<VSocket*> getOutputSockets()
    {
        return this->_outputSockets;
    }
    void setSocketDataType(int select,int index,VDataType type)
    {
        if(select==0){
            this->_inputSockets[index]->setDataType(type);
        }
        else{
            this->_outputSockets[index]->setDataType(type);
        }
    }

protected:
    QList<VSocket*> _inputSockets;
    QList<VSocket*> _outputSockets;

    VAction* _interaction;

    bool _canCompute = false;
    int _inputSocketNumber;
    int _outputSocketNumber;

    QString _title;
    QColor _titleColor;
    QGraphicsTextItem* _text;
    QGraphicsProxyWidget* _proxyContent;

    QPainterPath* _pathTitle;
    QPainterPath* _pathData;
    QPainterPath* _pathOutline;

    float _width = 180;
    float _height = 200;
    float _titleHeight = 24;
    float _edgeSize = 10.0;

};


#endif // VDESCRIPTOR_H
