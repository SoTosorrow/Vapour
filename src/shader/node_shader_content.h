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


#endif // NODESHADERCONTENT_H
