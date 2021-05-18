#ifndef NODESHADER_H
#define NODESHADER_H



#include<QGraphicsItem>
#include<QGraphicsTextItem>
#include<QGraphicsProxyWidget>
#include<QtGui>

#include"types.h"
#include"node_shader_content.h"

class NodeShader : public QGraphicsItem
{
public:
    NodeShader()=default;
    NodeShader(QString node_name);
    NodeShader(const NodeShader& node_item);
    void operator=(const NodeShader &node_item);

    ~NodeShader();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    bool contains(const QPointF &point) const override;
    int type() const override {return Type_NodeItem;}

    void setTitle(QString title);
    virtual void initDataNum(int input_data_number,int output_data_number){
        for(int i=0;i<input_data_number;i++){
            this->input_datas.append({0});
        }
        for(int i=0;i<output_data_number;i++){
            this->output_datas.append({0});
        }
    }
    virtual void initData(){}
    virtual void handle(){}

    QList<ShaderData> input_datas;
    QList<ShaderData> output_datas;


public:
    QString title;
    QColor title_color;
    QGraphicsTextItem *text;
    QGraphicsProxyWidget *proxyContent;
    NodeShaderContent *content;

    QPainterPath *path_title;
    QPainterPath *path_data;
    QPainterPath *path_outline;

    int input_data_number=0;
    int output_data_number=0;
    bool canCompute = true;

public:
    float width = 180; // 节点大小
    float title_height = 24;
    float height = 100;
    float edge_size = 10.0;
};


class NodeShaderInput : public NodeShader
{
public:
    NodeShaderInput():NodeShader("Input"){
        NodeShader::height = 80;
        this->content = new NodeShaderContentInput();
        this->content->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        NodeShader::proxyContent->setWidget(this->content);

    }
    ~NodeShaderInput(){
        delete content;
        this->content = nullptr;
    }
    void initDataNum(int input_data_number,int output_data_number) override{
        this->input_data_number = input_data_number;
        this->output_data_number = output_data_number;
        for(int i=0;i<input_data_number;i++){
            this->input_datas.append({0});
        }
        for(int i=0;i<output_data_number;i++){
            this->output_datas.append({0});
        }
    }
    void initData() override{
    }
    void handle() override{
    }

    int type() const override {return Type_NodeItemNumber;}
public:
    NodeShaderContentInput* content;
};

class NodeShaderOutput : public NodeShader
{
public:
    NodeShaderOutput():NodeShader("Input"){
        NodeShader::height = 80;
        this->content = new NodeShaderContentOutput();
        this->content->setGeometry(edge_size, title_height+0.5*edge_size,
                                   width - 2*edge_size,height - 2*edge_size - title_height);
        NodeShader::proxyContent->setWidget(this->content);

    }
    ~NodeShaderOutput(){
        delete content;
        this->content = nullptr;
    }
    void initDataNum(int input_data_number,int output_data_number) override{
        this->input_data_number = input_data_number;
        this->output_data_number = output_data_number;
        for(int i=0;i<input_data_number;i++){
            this->input_datas.append({0});
        }
        for(int i=0;i<output_data_number;i++){
            this->output_datas.append({0});
        }
    }
    void initData() override{
    }
    void handle() override{
    }

    int type() const override {return Type_NodeItemNumber;}
public:
    NodeShaderContentOutput* content;
};


#endif // NODESHADER_H
