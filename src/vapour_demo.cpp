#include <QApplication>
#include<QDir>
#include"vapour_win.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/core/core.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(a.applicationDirPath());  // 设置相对路径：是必需的、但能否改动？

//    VideoCapture cap;
//    cap.open(0);
//    qDebug()<<cap.open(0);
//    while (1) {
//        Mat frame;
//        cap >> frame;
//        imshow("1",frame);
//        if(waitKey(10)>=0)
//            break;
//    }
//    return 0;


    VapourWin win;
    win.show();

    return a.exec();
}
