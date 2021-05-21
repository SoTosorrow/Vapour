#ifndef VAPOUR_ACTION_DEVELOP_H
#define VAPOUR_ACTION_DEVELOP_H

#include"vapour_action.h"

class VapourActionEdit : public VapourAction
{
public:
    VapourActionEdit(){
        QLineEdit *temp = new QLineEdit("0",this);
        temp->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
        temp->setAlignment(Qt::AlignRight);
        edits.append(temp);
    }
    VapourActionEdit(int n){
        for(int i=0;i<n;i++){
            QLineEdit *temp = new QLineEdit("0",this);
            temp->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
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
    VapourActionText(){
        QLabel *temp = new QLabel("0",this);
        temp->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
        temp->setAlignment(Qt::AlignLeft);
        edits.append(temp);
    }
    VapourActionText(int n){
        for(int i=0;i<n;i++){
            edits.append(new QLabel("0",this));
        }
    }
    ~VapourActionText(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QLabel*> edits;
};


#endif // VAPOUR_ACTION_DEVELOP_H
