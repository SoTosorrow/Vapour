#include <QApplication>


#include"editor_win.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditorWin w;
    w.show();

    return a.exec();
}
