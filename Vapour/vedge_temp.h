#pragma once
#ifndef VEDGETEMP_H
#define VEDGETEMP_H

#include<QGraphicsPathItem>
#include<QPen>
#include<QPainterPath>
#include<QPainter>


class VEdgeTemp : public QGraphicsPathItem
{
public:
    VEdgeTemp()=default;
    VEdgeTemp(QPointF start,QPointF end,QGraphicsItem *parent = nullptr);
    VEdgeTemp(const VEdgeTemp& edge);
    void operator=(const VEdgeTemp& edge);
    ~VEdgeTemp()=default;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

    void setEndPos(QPointF end);
    void setStartPos(QPointF start);

private:
    QPainterPath _path;
    QPointF _startPos;
    QPointF _endPos;

};

#endif // VEDGETEMP_H
