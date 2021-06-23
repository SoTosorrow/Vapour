#ifndef VAPOUREDGETEMP_H
#define VAPOUREDGETEMP_H

#include<QGraphicsPathItem>
#include<QPen>
#include<QPainterPath>
#include<QPainter>

class VapourEdgeTemp : public QGraphicsPathItem
{
public:
    VapourEdgeTemp()=default;
    VapourEdgeTemp(QPointF start,QPointF end,QGraphicsItem *parent = nullptr);
    VapourEdgeTemp(const VapourEdgeTemp& edge);
    void operator=(const VapourEdgeTemp& edge);
    ~VapourEdgeTemp()=default;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

    void setEndPos(QPointF end);
    void setStartPos(QPointF start);


private:
    QPointF start_pos;
    QPointF end_pos;
    QPainterPath path;
};

#endif // VAPOUREDGETEMP_H
