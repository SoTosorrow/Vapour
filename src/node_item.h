#pragma once
#ifndef NODEITEM_H
#define NODEITEM_H

#include<QGraphicsItem>
#include<QGraphicsTextItem>
#include<QtGui>

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

    void setTitle(QString title);


public:
    QString title;
    QColor title_color;
    QGraphicsTextItem *text;

    QPainterPath *path_title;
    QPainterPath *path_data;
    QPainterPath *path_outline;

public:
    float width = 180; // 节点大小
    float title_height = 24;
    float height = 100;
    float edge_size = 10.0;
};

#endif // NODEITEM_H
