#include <QApplication>


#include"editor_win.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(a.applicationDirPath());  // 设置相对路径：是必需的、但能否改动？

    EditorWin w;
    w.show();

    return a.exec();
}
