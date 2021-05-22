#ifndef VAPOUR_DESCRIPTOR_CV_H
#define VAPOUR_DESCRIPTOR_CV_H

#include"vapour_descriptor.h"
#include"vapour_action_cv.h"

class VapourDescriptorCvInput : public VapourDescriptor
{
public:
    VapourDescriptorCvInput();
    VapourDescriptorCvInput(int in_num,int out_num,QString node_name,int edit_number=1)
        :VapourDescriptor(in_num,out_num,node_name,edit_number){
        // cv::Mat m(250, 250, CV_8UC3, cv::Scalar(255, 255, 255));
        cv::Mat m = cv::imread("C:\\Users\\Cuimi\\Desktop\\111.jpg");
        interaction = new VapourActionCvShow(m,edit_number);
        this->interaction->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        this->proxyContent->setWidget(this->interaction);
    }
    //VapourActionCvShow* interaction;
    VapourActionCvShow* interaction;
};

#endif // VAPOUR_DESCRIPTOR_CV_H
