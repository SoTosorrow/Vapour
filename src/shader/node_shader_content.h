#ifndef NODESHADERCONTENT_H
#define NODESHADERCONTENT_H

#include <QWidget>
#include<QtGui>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QLabel>
#include <QTextEdit>
#include<QDebug>

class NodeShaderContent: public QWidget
{
public:
    NodeShaderContent();
    ~NodeShaderContent(){
        delete layout;
        layout = nullptr;
    }
    QVBoxLayout *layout;


};

class NodeShaderContentInput : public NodeShaderContent
{
public:
    NodeShaderContentInput(){
        edit->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignRight);
    }
    ~NodeShaderContentInput(){
        delete edit;
        edit = nullptr;
    }
public:
    QLineEdit *edit = new QLineEdit("0",this);
};

class NodeShaderContentOutput : public NodeShaderContent
{
public:
    NodeShaderContentOutput(){
        edit->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignLeft);
    }
    ~NodeShaderContentOutput(){
        delete edit;
        edit = nullptr;
    }
public:
    QLabel *edit = new QLabel("0",this);
};

class NodeShaderContentFunc : public NodeShaderContent
{
public:
    NodeShaderContentFunc(QString func){
        edit->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignLeft);
        this->edit->setText(func);
    }
    ~NodeShaderContentFunc(){
        delete edit;
        edit = nullptr;
    }
public:
    QLabel *edit = new QLabel("0",this);
};

class NodeShaderContentCircle : public NodeShaderContent
{
public:
    NodeShaderContentCircle(){
        edit->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignRight);
        edit1->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
        edit1->setAlignment(Qt::AlignRight);
        edit1->setGeometry(0,40,100,30);
        edit2->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
        edit2->setAlignment(Qt::AlignRight);
        edit2->setGeometry(0,80,100,30);
    }
    ~NodeShaderContentCircle(){
        delete edit;
        edit = nullptr;
        delete edit1;
        edit1 = nullptr;
        delete edit2;
        edit2 = nullptr;
    }
public:
    QLineEdit *edit = new QLineEdit("0",this);
    QLineEdit *edit1 = new QLineEdit("1",this);
    QLineEdit *edit2 = new QLineEdit("2",this);
};

#endif // NODESHADERCONTENT_H
