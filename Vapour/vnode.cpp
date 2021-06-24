#include "vnode.h"
#include "vedge.h"


VNode::VNode(QWidget *parent)
    :QWidget(parent)
{
    initSocketNumber(1,1);
    this->setDesc(new VDescriptorInput(1,1));
    setTitle("just a test node");
}
VNode::VNode(const VNode &node,QWidget *parent)
    :QWidget(parent)
{
    Q_UNUSED(node);
}
VNode::~VNode()
{
    qDebug()<<"Delete: VapourNode";
    qDeleteAll(_inputNodes);
    qDeleteAll(_outputNodes);
    qDeleteAll(_inputDatas);
    qDeleteAll(_outputDatas);


    //delete edge


    delete _desc;
    _inputNodes.clear();
    _outputNodes.clear();
    _inputDatas.clear();
    _outputDatas.clear();
    _desc = nullptr;

}
void VNode::operator=(const VNode &node)
{
     Q_UNUSED(node);
}
void VNode::initSocketNumber(int inputSocketNumber,int outputSocketNumber)
{
    this->_inputSocketNumber = inputSocketNumber;
    this->_outputSocketNumber = outputSocketNumber;
}

VNodeType VNode::getType()
{
    return VNodeTypeBasic;
}
void VNode::setPos(QPointF pos)
{
    return this->_desc->setPos(pos);
}
QPointF VNode::getPos()
{
    return this->_desc->pos();
}
void VNode::setTitle(QString title)
{
    this->_desc->setTitle(title);
}
void VNode::setDesc(VDescriptor* desc)
{
    this->_desc = desc;
}
VDescriptor* VNode::getDesc()
{
    return this->_desc;
}

void VNode::addInputNode(VNode *node)
{
    this->_inputNodes.append(node);
}

void VNode::addOutputNode(VNode *node)
{
    this->_outputNodes.append(node);
}

void VNode::addInputEdge(VEdge *edge)
{
    this->_inputEdges.append(edge);
}

void VNode::addOutputEdge(VEdge *edge)
{
    this->_outputEdges.append(edge);
}

void VNode::delInputNode(VNode *node)
{
    this->_inputNodes.removeOne(node);
}

void VNode::delOutputNode(VNode *node)
{
    this->_outputNodes.removeOne(node);
}

void VNode::delInputEdge(VEdge *edge)
{
    this->_inputEdges.removeOne(edge);
}

void VNode::delOutputEdge(VEdge *edge)
{
    this->_outputEdges.removeOne(edge);
}

void VNode::setInputData(int index, VData *data)
{
//    this->_inputDatas[index].setData(data);
    Q_UNUSED(index);
    Q_UNUSED(data);
//    this->_inputDatas[index]->setData(data);
}


