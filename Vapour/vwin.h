#pragma once
#ifndef VWIN_H
#define VWIN_H

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

#include "vview.h"

class VWin : public QWidget
{
public:
    VWin(QWidget *parent = nullptr);
    ~VWin();
    void loadStyleSheet();


private:
    QString _styleFilePath;
    QVBoxLayout* _winLayout;
    VView* _view;
    VScene* _scene;
};

#endif // VWIN_H
