#pragma once
#ifndef VACTION_CV_H
#define VACTION_CV_H

#include "vaction.h"
#include "types.h"

class VActionCvInput : public VAction
{
public:
    VActionCvInput(int n=1){
        Q_UNUSED(n);
        QLineEdit* edit = new QLineEdit("C:\\Users\\Cuimi\\Desktop\\1.png",this);
        edit->setAlignment(Qt::AlignLeft);
        edit->setGeometry(0,0,150,25);
        edits.append(edit);

    }
    ~VActionCvInput(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QLineEdit*> edits;




};

class VActionCvStringParams : public VAction
{
public:
    VActionCvStringParams(int n=1){
        for(int i=0;i<n;i++){
            QLineEdit* edit = new QLineEdit("1",this);
            edit->setAlignment(Qt::AlignLeft);
            edit->setGeometry(0,i*30,100,25);
            edits.append(edit);
        }

    }
    ~VActionCvStringParams(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QLineEdit*> edits;


};
#endif // VACTION_CV_H
