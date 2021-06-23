#include "editor_win.h"



EditorWin::EditorWin(QWidget *parent)
    :QWidget(parent)
{
    qDebug()<<"Create: EditorWin";
    this->file_name = "reply/nodestyle.qss";
    //qDebug()<<QDir::currentPath();

    this->layout = new QVBoxLayout(); // 垂直布局
    this->editorScene = new EditorScene();
    this->editorView = new EditorView(this->editorScene,this);      // 设置view
    this->tempItem = nullptr;  // 空指针


    this->layout->addWidget(this->editorView);     //将view添加到布局中

    this->setGeometry(200,200,800,600);
    this->layout->setContentsMargins(0,0,0,0);  //与四周边缘距离为0
    this->setLayout(this->layout);  // 设置布局


    this->LoadStyleSheet();
    this->setWindowTitle("NewEditor");
    this->show();
}

EditorWin::~EditorWin()
{
    delete this->layout;
    this->layout = nullptr;
}



void EditorWin::LoadStyleSheet(){
    qDebug()<<"qss load:"<<this->file_name;
    qDebug()<<"----------";

    QFile file(this->file_name);
    file.open(QFile::ReadOnly | QFile::Text);  // 读取文件全部内容，使用tr()函数将其转换为QString类型
    QString stylesheet = QObject::tr(file.readAll());
    qApp->setStyleSheet(stylesheet);
    file.close();
}
