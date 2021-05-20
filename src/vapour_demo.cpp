#include <QApplication>
#include<QDir>
#include"vapour_win.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(a.applicationDirPath());  // 设置相对路径：是必需的、但能否改动？
    VapourWin win;
    win.show();

    return a.exec();
}
