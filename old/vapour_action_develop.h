#ifndef VAPOUR_ACTION_DEVELOP_H
#define VAPOUR_ACTION_DEVELOP_H

#include"vapour_action.h"
#include<QObject>
class VapourActionEdit : public VapourAction
{
public:
    VapourActionEdit(int n=1){
        for(int i=0;i<n;i++){
            QLineEdit *temp = new QLineEdit("0",this);
            //temp->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
            temp->setAlignment(Qt::AlignRight);
            temp->setGeometry(0,i*30,100,25);
            edits.append(temp);
        }
    }
    ~VapourActionEdit(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QLineEdit*> edits;
};

class VapourActionText : public VapourAction
{
public:
    VapourActionText(int n=1){
        for(int i=0;i<n;i++){
            QLabel *temp = new QLabel("0",this);
            // temp->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
            temp->setAlignment(Qt::AlignLeft);
            temp->setGeometry(0,i*30,100,25);
            edits.append(temp);
        }
    }
    ~VapourActionText(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QLabel*> edits;
};

class VapourActionButton : public VapourAction
{
public:
    VapourActionButton(int n=1,QString&& file_name=""){
        Q_UNUSED(file_name);
        for(int i=0;i<n;i++){
            QPushButton *temp = new QPushButton("button",this);
            temp->setStyleSheet("QPushButton { background-color:gray; border-radius:5px;font-size:20px; }");
            temp->setGeometry(0,i*30,100,25);
            edits.append(temp);
        }
        connect(this->edits[0], &QPushButton::clicked, this, [=](){
                this->edits[0]->setText("HMY NB");
            });
    }
    ~VapourActionButton(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QPushButton*> edits;



};


#endif // VAPOUR_ACTION_DEVELOP_H
