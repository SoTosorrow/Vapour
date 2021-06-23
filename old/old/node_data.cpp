#include "node_data.h"


NodeData::NodeData(QWidget *parent)
    :QWidget(parent)
{
    this->layout = new QVBoxLayout();
    this->layout->setContentsMargins(0,0,0,0);
    this->setLayout(this->layout);
}

NodeData::~NodeData()
{

}

NodeDataNumberInput::NodeDataNumberInput(QWidget *parent)
    :NodeData(parent)
{
    edit->setStyleSheet("QLineEdit { background: gray; border-radius:5px;font-size:20px; }");
    edit->setAlignment(Qt::AlignRight);
}

void NodeDataNumberInput::handle()
{
    qDebug()<<"handle";
}

void NodeDataNumberInput::transferData()
{
    qDebug()<<"transfer data";
}

NodeDataNumberInput::~NodeDataNumberInput()
{
    delete this->edit;
    this->edit = nullptr;
}
