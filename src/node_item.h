#pragma once
#ifndef NODEITEM_H
#define NODEITEM_H

#include<QGraphicsItem>
#include<QGraphicsTextItem>
#include<QGraphicsProxyWidget>
#include<QtGui>

#include"node_inter.h"
#include"types.h"

class NodeItem : public QGraphicsItem
{
public:
    NodeItem()=default;
    NodeItem(QString node_name);
    NodeItem(const NodeItem& node_item);
    void operator=(const NodeItem &node_item);

    ~NodeItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    bool contains(const QPointF &point) const override;
    int type() const override {return Type_NodeItem;}

    void setTitle(QString title);
//    virtual void handle(){qDebug()<<"handle";}
//    virtual void transferData(){qDebug()<<"transferData";}


public:
    QString title;
    QColor title_color;
    QGraphicsTextItem *text;
    QGraphicsProxyWidget *proxyContent;
    NodeInter* inter;

    QPainterPath *path_title;
    QPainterPath *path_data;
    QPainterPath *path_outline;

public:
    float width = 180; // 节点大小
    float title_height = 24;
    float height = 100;
    float edge_size = 10.0;
};


class NodeItemNumberInput : public NodeItem
{
public:
    NodeItemNumberInput():NodeItem("Input"){
        NodeItem::height = 80;
        this->inter = new NodeInterInput();
        this->inter->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        NodeItem::proxyContent->setWidget(this->inter);

    }
    ~NodeItemNumberInput(){
        delete inter;
        this->inter = nullptr;
    }
    int type() const override {return Type_NodeItemNumber;}
public:
    NodeInterInput* inter;
};

class NodeItemNumberOutput : public NodeItem
{
public:
    NodeItemNumberOutput():NodeItem("Output"){
        NodeItem::height = 80;
        this->inter = new NodeInterOutput();
        this->inter->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        NodeItem::proxyContent->setWidget(this->inter);

    }
    ~NodeItemNumberOutput(){
        delete inter;
        this->inter = nullptr;
    }
    int type() const override {return Type_NodeItemOutput;}
public:
    NodeInterOutput* inter;
};

class NodeItemNumberAdd : public NodeItem
{
public:
    NodeItemNumberAdd():NodeItem("Add"){
        NodeItem::height = 80;
        this->inter = new NodeInterAdd();
        this->inter->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        NodeItem::proxyContent->setWidget(this->inter);

    }
    ~NodeItemNumberAdd(){
        delete inter;
        this->inter = nullptr;
    }
    int type() const override {return Type_NodeItemAdd;}
public:
    NodeInterAdd* inter;
};

class NodeItemNumberMul : public NodeItem
{
public:
    NodeItemNumberMul():NodeItem("Mul"){
        NodeItem::height = 80;
        this->inter = new NodeInterMul();
        this->inter->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        NodeItem::proxyContent->setWidget(this->inter);

    }
    ~NodeItemNumberMul(){
        delete inter;
        this->inter = nullptr;
    }
    int type() const override {return Type_NodeItemMul;}
public:
    NodeInterMul* inter;
};

class NodeItemNumberSub : public NodeItem
{
public:
    NodeItemNumberSub():NodeItem("Sub"){
        NodeItem::height = 80;
        this->inter = new NodeInterSub();
        this->inter->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        NodeItem::proxyContent->setWidget(this->inter);

    }
    ~NodeItemNumberSub(){
        delete inter;
        this->inter = nullptr;
    }
    int type() const override {return Type_NodeItemSub;}
public:
    NodeInterSub* inter;
};

class NodeItemNumberDiv : public NodeItem
{
public:
    NodeItemNumberDiv():NodeItem("Div"){
        NodeItem::height = 80;
        this->inter = new NodeInterDiv();
        this->inter->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        NodeItem::proxyContent->setWidget(this->inter);

    }
    ~NodeItemNumberDiv(){
        delete inter;
        this->inter = nullptr;
    }
    int type() const override {return Type_NodeItemDiv;}
public:
    NodeInterDiv* inter;
};


#endif // NODEITEM_H
