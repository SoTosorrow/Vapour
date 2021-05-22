#include "vapour_win.h"

VapourWin::VapourWin(QWidget *parent)
    :QWidget(parent)
{
    qDebug()<<"Create: VapourWin";
    //this->setAttribute(Qt::WA_StyledBackground,true);
    this->style_file_name = "reply/nodestyle.qss";

    this->win_layout = new QVBoxLayout(); // 垂直布局
    this->vapour_scene = new VapourScene();
    this->vapour_view = new VapourView(this->vapour_scene,this);      // 设置view
    this->win_layout->addWidget(this->vapour_view);     //将view添加到布局中

    this->setGeometry(200,200,800,600);
    this->win_layout->setContentsMargins(0,0,0,0);  //与四周边缘距离为0
    this->setLayout(this->win_layout);  // 设置布局

    // this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    // this->setStyleSheet("background-color: #262626;");
    this->LoadStyleSheet();
    this->setWindowTitle("developEditor");
    this->show();
}

VapourWin::~VapourWin()
{
    delete this->win_layout;
    this->win_layout = nullptr;
}

void VapourWin::LoadStyleSheet()
{
    qDebug()<<"LoadQss:"<<this->style_file_name;

    QFile file(this->style_file_name);
    file.open(QFile::ReadOnly | QFile::Text);  // 读取文件全部内容，使用tr()函数将其转换为QString类型
    QString stylesheet = QObject::tr(file.readAll());
    qApp->setStyleSheet(stylesheet);
    // qDebug()<<stylesheet;
    file.close();
}



