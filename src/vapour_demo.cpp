#include <QApplication>
#include<QDir>
#include"vapour_win.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(a.applicationDirPath());  // 设置相对路径：是必需的、但能否改动？

//    QString qss_file = "reply/nodestyle.qss";
//    qDebug()<<"LoadQss:"<<qss_file;
//    QFile file(qss_file);
//    file.open(QFile::ReadOnly | QFile::Text);  // 读取文件全部内容，使用tr()函数将其转换为QString类型
//    QString stylesheet = QObject::tr(file.readAll());
//    qApp->setStyleSheet(stylesheet);
//    file.close();


    VapourWin win;
    win.show();

    return a.exec();
}
