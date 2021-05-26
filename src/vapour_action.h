#ifndef VAPOURACTION_H
#define VAPOURACTION_H


#include <QWidget>
#include<QtGui>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QLabel>
#include<QTextEdit>
#include<QDebug>
#include<QList>
#include<QPushButton>


class VapourAction: public QWidget
{
public:
    VapourAction(int n=1){
        edit_layout = new QVBoxLayout();
        this->edit_layout->setContentsMargins(0,0,0,0);
        this->setLayout(this->edit_layout);
        setEditNumber(n);
    }
    void setEditNumber(int n){
        this->edit_number = n;
    }
    virtual ~VapourAction(){
        delete edit_layout;
        edit_layout = nullptr;
    }

public:
    QVBoxLayout *edit_layout;
    int edit_number;
};



#endif // VAPOURACTION_H
