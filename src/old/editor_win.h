#pragma once
#ifndef EDITORWIN_H
#define EDITORWIN_H


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
// #include<memory>


#include"editor_scene.h"
#include"editor_view.h"


class EditorWin : public QWidget
{
    Q_OBJECT

public:
    EditorWin(QWidget *parent = nullptr);
    // 拷贝构造函数
    // 移动构造函数
    ~EditorWin();  // 析构函数

    void LoadStyleSheet();



public:
    QVBoxLayout* layout;
    QGraphicsItem* tempItem;
    EditorView* editorView;
    EditorScene* editorScene;



private:
    QString file_name;


};









#endif // EDITORWIN_H
