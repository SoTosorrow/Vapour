#pragma once
#ifndef VACTION_DEVELOP_H

#include "vaction.h"

class VActionEdit : public VAction
{
public:
    VActionEdit(int n=1)
    {
        for(int i=0;i<n;i++){
            QLineEdit *temp = new QLineEdit("0",this);
            //temp->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
            temp->setAlignment(Qt::AlignRight);
            temp->setGeometry(0,i*30,100,25);
            _edits.append(temp);
        }
    }
    ~VActionEdit()
    {
        qDeleteAll(_edits);
        _edits.clear();
    }


public:
    QList<QLineEdit*> _edits;
};

class VActionText : public VAction
{
public:
    VActionText(int n=1){
        for(int i=0;i<n;i++){
            QLabel *temp = new QLabel("0",this);
            // temp->setStyleSheet("QLabel { border-radius:5px;font-size:20px; }");
            temp->setAlignment(Qt::AlignLeft);
            temp->setGeometry(0,i*30,100,25);
            _edits.append(temp);
        }
    }
    ~VActionText(){
        qDeleteAll(_edits);
        _edits.clear();
    }

public:
    QList<QLabel*> _edits;
};

class VActionButton : public VAction
{
public:
    VActionButton(int n=1,QString&& file_name=""){
        Q_UNUSED(file_name);
        for(int i=0;i<n;i++){
            QPushButton *temp = new QPushButton("button",this);
            temp->setStyleSheet("QPushButton { background-color:gray; border-radius:5px;font-size:20px; }");
            temp->setGeometry(0,i*30,100,25);
            _edits.append(temp);
        }
        connect(this->_edits[0], &QPushButton::clicked, this, [=](){
                this->_edits[0]->setText("test");
            });
    }
    ~VActionButton(){
        qDeleteAll(_edits);
        _edits.clear();
    }

public:
    QList<QPushButton*> _edits;



};

#endif
