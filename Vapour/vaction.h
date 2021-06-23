#pragma once
#ifndef VACTION_H
#define VACTION_H

#include <QWidget>
#include<QtGui>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QLabel>
#include<QTextEdit>
#include<QDebug>
#include<QList>
#include<QPushButton>

class VAction: public QWidget
{
public:
    VAction(int n=1){
        _editLayout = new QVBoxLayout();
        this->_editLayout->setContentsMargins(0,0,0,0);
        this->setLayout(this->_editLayout);
        setEditNumber(n);
    }
    void setEditNumber(int n){
        this->_editNumber = n;
    }
    virtual ~VAction(){
        delete _editLayout;
        _editLayout = nullptr;
    }

protected:
    QVBoxLayout* _editLayout;
    int _editNumber;

};

#endif // VACTION_H
