#pragma once
#ifndef EDITORSCENE_H
#define EDITORSCENE_H


#include<QWidget>
#include<QGraphicsScene>
#include<QColor>
#include<QLine>
#include<QPen>
#include<QPainter>
#include<QRectF>
#include<math.h>


class EditorScene : public QGraphicsScene
{
public:
    EditorScene(QWidget *parent=nullptr);
    ~EditorScene();

    // 绘制背景
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    // 设置场景大小
    void SetScene(int width,int height);




private:
    // 背景绘制样式
    QColor color_background;
    QColor color_light;
    QColor color_dark;
    QPen pen_light;
    QPen pen_dark;

    // 背景绘制参数
    int gridSize=20;
    int gridSquare=5;
    int scene_width = 6400;
    int scene_height = 6400;

    int left;
    int right;
    int top;
    int bottom;
    int prime_left;
    int prime_top;
};
#endif // EDITORSCENE_H
