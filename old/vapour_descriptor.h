#pragma once
#ifndef VAPOURDESCRIPTOR_H
#define VAPOURDESCRIPTOR_H

#include<QGraphicsItem>
#include<QGraphicsTextItem>
#include<QGraphicsProxyWidget>
#include<QtGui>
#include<QList>
#include"vapour_socket.h"
#include"vapour_action_develop.h"
// 负责节点UI的呈现

class VapourDescriptor : public QGraphicsItem
{
public:
    VapourDescriptor(QString node_name);
    VapourDescriptor(int in_num,int out_num,QString node_name,int edit_number=1);
    VapourDescriptor(const VapourDescriptor& desc);
    void operator=(const VapourDescriptor &desc);
    virtual ~VapourDescriptor();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    bool contains(const QPointF &point) const override;

    void setSocketNumber(int in_num,int out_num){
        this->input_socket_number = in_num;
        this->output_socket_number = out_num;
    }
    void initSocket(){
        for(int i=0;i<this->input_socket_number;i++){
            // temp是否正确释放
            VapourSocket* temp =  new VapourSocket(this);
            temp->setPos(0,i*30+40);
            temp->setIndex(i);
            input_sockets.append(temp);
        }
        for(int j=0;j<this->output_socket_number;j++){
            VapourSocket* temp =  new VapourSocket(this);
            temp->setPos(width,j*20+34);
            temp->setIndex(j);
            output_sockets.append(temp);
        }
    }
    void setTitle(QString title){
        this->text->setPlainText(title);
    }
    void setDescWidth(float w){
        this->width = w;
        for(int j=0;j<output_socket_number;j++){
            output_sockets[j]->setPos(width,j*20+34);
        }
    }
    void setDescHeight(float h){
        this->height = h;
    }
    void setShape(int type=0){
        if(type==0){
            // 节点shape
        }
        if(type==1){
            // 门电路shape
        }
        else{

        }
    }
    virtual QPointF getPos(){
        return this->pos();
    }
    virtual void setText(int n,QString t){
        this->interaction->edits[n]->setText(t);
    }
    virtual double getText(int n){
        return this->interaction->edits[n]->text().toDouble();
    }
    virtual QString getFile(){
        return {};
    }
    virtual void test_T_image(cv::Mat m){
        Q_UNUSED(m);
    }
    virtual QList<QString> getParams(){
        return {};
    }



public:
    // QList<QString> params;
    QList<VapourSocket*> input_sockets;
    QList<VapourSocket*> output_sockets;

    VapourActionEdit* interaction;


    bool can_compute = true;
    bool input_is_union_socket = false;
    int input_socket_number;
    int output_socket_number;

    QString title;
    QColor title_color;
    QGraphicsTextItem *text;
    QGraphicsProxyWidget *proxyContent;

    QPainterPath *path_title;
    QPainterPath *path_data;
    QPainterPath *path_outline;

public:
    float width = 180; // 节点宽度
    float title_height = 24;
    float height = 200;
    float edge_size = 10.0;
};

#endif // VAPOURDESCRIPTOR_H
