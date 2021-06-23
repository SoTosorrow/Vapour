#pragma once
#ifndef VAPOURWIN_H
#define VAPOURWIN_H

#include<QWidget>
#include<QDebug>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QGraphicsTextItem>
#include<QVBoxLayout>
#include<QPushButton>
#include<QBrush>
#include<QTextEdit>
#include<QGraphicsProxyWidget>
#include<QString>
#include<QFile>
#include<QApplication>
#include<QGraphicsWidget>
#include"vapour_view.h"

class VapourWin : public QWidget
{
public:
    VapourWin(QWidget *parent = nullptr);
    ~VapourWin();
    void LoadStyleSheet();


public:
    QVBoxLayout* win_layout;
    VapourView* vapour_view;
    VapourScene* vapour_scene;

private:
    QString style_file_name;

};

#endif // VAPOURWIN_H
