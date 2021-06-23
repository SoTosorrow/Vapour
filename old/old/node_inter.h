#ifndef NODEINTER_H
#define NODEINTER_H

#include <QWidget>
#include<QtGui>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QLabel>
#include <QTextEdit>
#include<QDebug>

class NodeInter: public QWidget
{
public:
    NodeInter();
    ~NodeInter(){
        delete layout;
        layout = nullptr;
    }
    QVBoxLayout *layout;


};

class NodeInterInput : public NodeInter
{
public:
    NodeInterInput(){
        edit->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignRight);
    }
    ~NodeInterInput(){
        delete edit;
        edit = nullptr;
    }
public:
    QLineEdit *edit = new QLineEdit("0",this);
};

class NodeInterOutput : public NodeInter
{
public:
    NodeInterOutput(){
        edit->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignLeft);
    }
    ~NodeInterOutput(){
        delete edit;
        edit = nullptr;
    }
public:
    QLabel *edit = new QLabel("0",this);
};

class NodeInterAdd : public NodeInter
{
public:
    NodeInterAdd(){
        edit->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignLeft);
    }
    ~NodeInterAdd(){
        delete edit;
        edit = nullptr;
    }
public:
    QLabel *edit = new QLabel("+",this);
};

class NodeInterMul : public NodeInter
{
public:
    NodeInterMul(){
        edit->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignLeft);
    }
    ~NodeInterMul(){
        delete edit;
        edit = nullptr;
    }
public:
    QLabel *edit = new QLabel("*",this);
};

class NodeInterSub : public NodeInter
{
public:
    NodeInterSub(){
        edit->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignLeft);
    }
    ~NodeInterSub(){
        delete edit;
        edit = nullptr;
    }
public:
    QLabel *edit = new QLabel("-",this);
};

class NodeInterDiv : public NodeInter
{
public:
    NodeInterDiv(){
        edit->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
        edit->setAlignment(Qt::AlignLeft);
    }
    ~NodeInterDiv(){
        delete edit;
        edit = nullptr;
    }
public:
    QLabel *edit = new QLabel("/",this);
};

#endif // NODEINTER_H
