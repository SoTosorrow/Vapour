#ifndef VAPOUR_ACTION_CV_H
#define VAPOUR_ACTION_CV_H

#include"vapour_action.h"
#include"vapour_types.h"

class VapourActionCvShow : public VapourAction
{
public:
    VapourActionCvShow(cv::Mat m,int n=1){
        Q_UNUSED(n);
        Q_UNUSED(m);
        QLineEdit* edit1 = new QLineEdit("1",this);
        edit1->setAlignment(Qt::AlignLeft);
        edit1->setGeometry(0,0,150,25);
        QLineEdit* edit2 = new QLineEdit("1",this);
        edit2->setAlignment(Qt::AlignLeft);
        edit2->setGeometry(0,30,150,25);
        QLineEdit* edit3 = new QLineEdit("1",this);
        edit3->setAlignment(Qt::AlignLeft);
        edit3->setGeometry(0,60,150,25);
        QLineEdit* edit4 = new QLineEdit("1",this);
        edit4->setAlignment(Qt::AlignLeft);
        edit4->setGeometry(0,90,150,25);
        edits.append(edit1);
        edits.append(edit2);
        edits.append(edit3);
        edits.append(edit4);

//        button = new QPushButton("button",this);
//        button->setGeometry(0,30,100,25);
//        button->setStyleSheet("QPushButton { background-color:gray; border-radius:5px;font-size:20px; }");

//        connect(button, &QPushButton::clicked, this, [=](){
//                button->setText("CV Test");
//                cv::imshow("test",tm);
//            });
    }
    ~VapourActionCvShow(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QLineEdit*> edits;
//    QPushButton* button;
    cv::Mat tm;
    //QLineEdit* edit;



};


class VapourActionCvInput : public VapourAction
{
public:
    VapourActionCvInput(cv::Mat m,int n=1){
        Q_UNUSED(n);
        Q_UNUSED(m);
        QLineEdit* edit = new QLineEdit("C:\\Users\\Cuimi\\Desktop\\1.png",this);
        edit->setAlignment(Qt::AlignLeft);
        edit->setGeometry(0,0,150,25);
        edits.append(edit);

//        button = new QPushButton("button",this);
//        button->setGeometry(0,30,100,25);
//        button->setStyleSheet("QPushButton { background-color:gray; border-radius:5px;font-size:20px; }");

//        connect(button, &QPushButton::clicked, this, [=](){
//                button->setText("CV Test");
//                cv::imshow("test",tm);
//            });
    }
    ~VapourActionCvInput(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QLineEdit*> edits;
//    QPushButton* button;
    cv::Mat tm;
    //QLineEdit* edit;



};
#endif // VAPOUR_ACTION_CV_H
