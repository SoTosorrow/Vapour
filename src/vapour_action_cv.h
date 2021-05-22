#ifndef VAPOUR_ACTION_CV_H
#define VAPOUR_ACTION_CV_H

#include"vapour_action.h"
#include"vapour_types.h"

class VapourActionCvShow : public VapourAction
{
public:
    VapourActionCvShow(cv::Mat m,int n=1){
        for(int i=0;i<n;i++){
            QPushButton *temp = new QPushButton("button",this);
            temp->setStyleSheet("QPushButton { background-color:gray; border-radius:5px;font-size:20px; }");
            temp->setGeometry(0,i*30,100,25);
            edits.append(temp);
        }
        connect(this->edits[0], &QPushButton::clicked, this, [=](){
                this->edits[0]->setText("CV Test");
                cv::imshow("test",m);
            });
    }
    ~VapourActionCvShow(){
        qDeleteAll(edits);
        edits.clear();
    }

public:
    QList<QPushButton*> edits;



};
#endif // VAPOUR_ACTION_CV_H
