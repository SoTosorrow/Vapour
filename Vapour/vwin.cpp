#include "vwin.h"


VWin::VWin(QWidget *parent)
    :QWidget(parent)
{
    qDebug()<<"Create: VapourWin";
    //this->setAttribute(Qt::WA_StyledBackground,true);
    this->_styleFilePath = "reply/nodestyle.qss";

    this->_winLayout = new QVBoxLayout(); // 垂直布局
    this->_scene = new VScene();
    this->_view = new VView(this->_scene,this);      // 设置view
    this->_winLayout->addWidget(this->_view);     //将view添加到布局中

    this->setGeometry(200,200,800,600);
    this->_winLayout->setContentsMargins(0,0,0,0);  //与四周边缘距离为0
    this->setLayout(this->_winLayout);  // 设置布局

    // this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    // this->setStyleSheet("background-color: #262626;");
    this->loadStyleSheet();
    this->setWindowTitle("developEditor");
    this->show();

    qDebug()<<"Main thread"<<QThread::currentThreadId();
}

VWin::~VWin()
{
    delete this->_winLayout;
    this->_winLayout = nullptr;
    delete this->_view;
    this->_view = nullptr;
    delete this->_scene;
    this->_scene = nullptr;
}

void VWin::loadStyleSheet()
{
    qDebug()<<"LoadQss:"<<this->_styleFilePath;

    QFile file(this->_styleFilePath);
    file.open(QFile::ReadOnly | QFile::Text);
    QString stylesheet = QObject::tr(file.readAll());
    qApp->setStyleSheet(stylesheet);

    file.close();
}
