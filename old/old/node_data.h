#ifndef NODEDATA_H
#define NODEDATA_H

#include <QWidget>
#include<QtGui>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QLabel>
#include <QTextEdit>
#include<QDebug>

class NodeData : public QWidget
{
public:
    NodeData(QWidget *parent = nullptr);
    virtual void handle()=0;
    virtual void transferData()=0;
    ~NodeData();

private:
    QVBoxLayout *layout;
};

class NodeDataNumberInput : public NodeData
{
public:
    NodeDataNumberInput(QWidget *parent = nullptr);
    void handle() override;
    void transferData() override;
    ~NodeDataNumberInput();

private:
    QLineEdit *edit = new QLineEdit("0",this);
};

#endif // NODEDATA_H
