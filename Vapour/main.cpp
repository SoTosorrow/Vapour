#include <QApplication>
#include <QDir>
#include <QDebug>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/core/core.hpp>

#include "vwin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(a.applicationDirPath());

    VWin w;
    w.show();


    return a.exec();
}
