#include "node.h"

Node::Node(QWidget *parent)
    :QWidget(parent)
{
    qDebug()<<"Create: Test-node";
    //this->item = new NodeItem("test");
    shader_item = new NodeShader("test");

    initSocket(2,1);
}

Node::Node(int type, QWidget *parent)
    :QWidget(parent)
{
    if(type == 0){
        this->node_type = DATA_NUMBER;
        this->item = new NodeItemNumberInput();
        initSocket(0,1);
        return;
    }
    if(type == 1){
        this->node_type = DATA_NUMBER;
        this->item = new NodeItemNumberOutput();
        initSocket(1,0);
        return;
    }
    if(type == 2){
        this->node_type = DATA_NUMBER;
        this->item = new NodeItemNumberAdd();
        initSocket(2,1);
        return;
    }
    if(type == 3){
        this->node_type = DATA_NUMBER;
        this->item = new NodeItemNumberSub();
        initSocket(2,1);
        return;
    }
    if(type == 4){
        this->node_type = DATA_NUMBER;
        this->item = new NodeItemNumberMul();
        initSocket(2,1);
        return;
    }
    if(type == 5){
        this->node_type = DATA_NUMBER;
        this->item = new NodeItemNumberDiv();
        initSocket(2,1);
        return;
    }
    if(type == 10){
        this->node_type = DATA_SHADER;
        this->shader_item = new NodeShaderInput();
        initSocket(1,1);
        return;
    }
}

Node::~Node()
{
    qDebug()<<"Delete: Node";
    qDeleteAll(input_nodes);
    qDeleteAll(output_nodes);
    qDeleteAll(input_sockets);
    qDeleteAll(output_sockets);
    qDeleteAll(connect_sockets);
    this->input_nodes.clear();
    this->output_nodes.clear();
    this->input_sockets.clear();
    this->output_sockets.clear();
    this->connect_sockets.clear();
    delete this->item;
    this->item=nullptr;
    delete this->shader_item;
    this->shader_item=nullptr;
}

Node::Node(const Node &node, QWidget *parent)
    :QWidget(parent)
{
    Q_UNUSED(node);
}

void Node::operator=(const Node &node)
{
    Q_UNUSED(node);
}

void Node::setPos(QPointF pos)
{
    if(this->node_type == DATA_NUMBER)
        this->item->setPos(pos);
    if(this->node_type == DATA_SHADER)
        this->shader_item->setPos(pos);
}

void Node::setIndex(int index)
{
    this->index = index;
}

void Node::initSocket(int in, int out)
{
    this->input_socket_number =in;
    this->output_socket_number = out;
    for(int i=0;i<input_socket_number;i++){
        NodeSocket *socket;
        if(node_type==DATA_NUMBER)
            socket = new NodeSocket(DATA_NUMBER,item);
        if(node_type==DATA_SHADER)
            socket = new NodeSocket(DATA_SHADER,shader_item);
        socket->setPos(0,i*20+34);
        socket->setIndex(i);
        socket->setType(SOCKET_INPUT);
        input_sockets.append(socket);
    }
    for(int i=0;i<output_socket_number; i++){
        NodeSocket *socket2;
        if(node_type==DATA_NUMBER)
            socket2 = new NodeSocket(DATA_NUMBER,item);
        if(node_type==DATA_SHADER)
            socket2 = new NodeSocket(DATA_SHADER,shader_item);
        socket2->setPos(180,i*20+34);
        socket2->setIndex(i);
        socket2->setType(SOCKET_OUTPUT);

        output_sockets.append(socket2);

    }
    if(node_type==DATA_NUMBER)
        this->item->initDataNum(in,out);
    if(node_type==DATA_SHADER)
        this->shader_item->initDataNum(in,out);
}

void Node::transferData()
{
    // qDebug()<<"transfer number"<<this->output_nodes.length();
    // 对于每一个要传输数据的节点
    for(int i=0;i<this->output_nodes.length();i++){
        // 判断要把哪项数据传给对方QList中那项
        //qDebug()<<this->output_nodes[i]->index<<this->connect_sockets[i]->index;
        this->output_nodes[i]->item->input_datas[this->connect_sockets[i]->index] = this->item->output_datas[0];
        //qDebug()<<this->output_nodes[i]->index<<output_sockets[i]->connect_sockets[i]->index;
        //this->output_nodes[i]->item->input_datas[output_sockets[i]->connect_sockets[i]->index] = this->item->output_datas[0];



    }
}
