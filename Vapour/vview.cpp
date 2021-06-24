#include "vview.h"
#include "vnode_develop.h"

VView::VView(VScene* scene,QWidget *parent)
    :QGraphicsView(parent)
{
    qDebug()<<"Create: VapourView";
    this->_scene = scene;

    this->setScene(this->_scene);
    this->setRenderHints(QPainter::Antialiasing |
                         QPainter::HighQualityAntialiasing |
                         QPainter::TextAntialiasing |
                         QPainter::SmoothPixmapTransform);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  // 防止画线的bug？
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet(" background: rgb(255,255,255);");

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse); //设置锚点
    this->setDragMode(QGraphicsView::RubberBandDrag);  // 框选
}

VView::~VView()
{
    qDeleteAll(_nodes);
    qDeleteAll(_edges);
    qDeleteAll(_action);
    delete _scene;
    delete _computeThread;
    delete _edgeTemp;
    delete _edge;
    delete _mainMenu;
    delete _startNode;
    delete _endNode;
    delete _startSocket;
    delete _endSocket;
    _scene = nullptr;
    _computeThread = nullptr;
    _edgeTemp = nullptr;
    _edge = nullptr;
    _mainMenu = nullptr;
    _startNode = nullptr;
    _endNode = nullptr;
    _startSocket = nullptr;
    _endSocket = nullptr;

}

void VView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()== Qt::MiddleButton){
        this->middleMouseButtonPress(event);
    }
    else if(event->button() == Qt::LeftButton){
        leftMouseButtonPress(event);
    }
    else if(event->button() == Qt::RightButton){
        RightMouseButtonPress(event);
    }
    else{
        QGraphicsView::mousePressEvent(event);
    }
}

void VView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()== Qt::MiddleButton){
        this->middleMouseButtonRelease(event);
    }
    else if(event->button() == Qt::LeftButton){
        LeftMouseButtonRelease(event);
    }
    else if(event->button() == Qt::RightButton){
        RightMouseButtonRelease(event);
    }
    else{
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void VView::mouseMoveEvent(QMouseEvent *event)
{
    if(_isEdgeTempAlive){
        QPointF pos = mapToScene(event->pos());

        this->_edgeTemp->setEndPos(pos);
        this->_scene->update();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void VView::keyPressEvent(QKeyEvent *event)
{
    QPoint pos = this->cursor().pos();
    if((event->modifiers()== Qt::ShiftModifier) && event->key() == Qt::Key_A){
        addNode(_number++,pos);
        return;
    }
    if((event->modifiers()== Qt::ShiftModifier) && event->key() == Qt::Key_Q){
        queryNodeInfo();
        return;
    }
    if((event->modifiers()== Qt::ShiftModifier) && event->key() == Qt::Key_S){
        ergodicGraph();
        return;
    }
    if(event->key() == Qt::Key_Delete){
        deleteItem();
        return;
    }
    if((event->modifiers()== Qt::ShiftModifier) && event->key() == Qt::Key_D){
        copyItem();
        return;
    }

    QGraphicsView::keyPressEvent(event);
}

void VView::wheelEvent(QWheelEvent *event)
{
    // the factor of zoom
    float zoomOutFactor = 1 / this->_zoomInFactor;
    float zoomFactor;
    // store the scene pos
    QPointF *oldPos = new QPointF(this->mapToScene(event->pos()));
    Q_UNUSED(oldPos);
    if(event->angleDelta().y() > 0){
        zoomFactor = _zoomInFactor;
        _zoom += _zoomStep;
    }
    else{
        zoomFactor = zoomOutFactor;
        _zoom -= _zoomStep;
    }

    BOOLEAN clamped = false;  // 放缩的限制
    if(this->_zoom < _zoomRange[0]){
        this->_zoom = _zoomRange[0];
        clamped = true;
    }
    if(this->_zoom > _zoomRange[1]){
        this->_zoom = _zoomRange[1];
        clamped = true;
    }

    if(!clamped || !this->_zoomClamp)
        this->scale(zoomFactor,zoomFactor);  // set scene scale

    //TODO 清晰化
    /*
    QPointF *newPos = new QPointF(this->mapToScene(event->pos()));
    QPointF *delta = new QPointF(*newPos - *oldPos);
    this->translate(delta->x(),delta->y());
    this->translate(100.0,100.0);
    */
    // event->accept();
}

void VView::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    QPoint pos = this->cursor().pos();
    QPoint pos2 = this->mapFromGlobal(pos);
    pos2 = this->mapToGlobal(pos2);

    QString qss = "QMenu { background-color:#999999; \
                            padding:5px;\
                            }"
                "QMenu::item:selected {background-color : rgb(50,50,50)\
                            ;}"
                "QMenu::separator {\
                            height: 2px;\
                            margin-left: 10px;\
                            margin-right: 10px;\
                            }";

    _mainMenu = new QMenu();
    QMenu *numberMenu = new QMenu("Double");
    _mainMenu->setStyleSheet(qss);
    numberMenu->setStyleSheet(qss);

    QAction *addNode1 = numberMenu->addAction("Double");
    connect(addNode1, &QAction::triggered, [=]()
    {
        addNode(_number++,1,pos);
    });
    QAction *addNode2 = numberMenu->addAction("Double Add");
    connect(addNode2, &QAction::triggered, [=]()
    {
        addNode(_number++,2,pos);
    });
    QAction *addNode3 = numberMenu->addAction("Double Sub");
    connect(addNode3, &QAction::triggered, [=]()
    {
        addNode(_number++,3,pos);
    });
    QAction *addNode4 = numberMenu->addAction("Double Mul");
    connect(addNode4, &QAction::triggered, [=]()
    {
        addNode(_number++,4,pos);
    });
    QAction *addNode5 = numberMenu->addAction("Double Div");
    connect(addNode5, &QAction::triggered, [=]()
    {
        addNode(_number++,5,pos);
    });


    QMenu *matMenu = new QMenu("Mat");
    matMenu->setStyleSheet(qss);
    QAction *addNodeMat1 = matMenu->addAction("Mat Input");
    connect(addNodeMat1, &QAction::triggered, [=]()
    {
        addNode(_number++,6,pos);
    });
    QAction *addNodeMat2 = matMenu->addAction("Mat Convert");
    connect(addNodeMat2, &QAction::triggered, [=]()
    {
        addNode(_number++,7,pos);
    });
    QAction *addNodeMat3 = matMenu->addAction("Mat Threshold");
    connect(addNodeMat3, &QAction::triggered, [=]()
    {
        addNode(_number++,8,pos);
    });



    qDeleteAll(_action);
    _action.clear();

    _mainMenu->addMenu(numberMenu);
    _mainMenu->addMenu(matMenu);
    _mainMenu->popup(pos);
}

void VView::middleMouseButtonPress(QMouseEvent *event)
{
    QMouseEvent *releaseEvent =new QMouseEvent(QEvent::MouseButtonPress, event->localPos(),
                                           event->screenPos(), Qt::LeftButton, Qt::NoButton, event->modifiers());
    QGraphicsView::mouseReleaseEvent(releaseEvent);
    this->setDragMode(QGraphicsView::ScrollHandDrag);  // 设置鼠标形状
    QMouseEvent *fakeEvent = new QMouseEvent(event->type(),event->localPos(),event->screenPos(),
                                             Qt::LeftButton, event->buttons() | Qt::LeftButton ,event->modifiers());
    QGraphicsView::mouseReleaseEvent(fakeEvent);

    delete releaseEvent;
    delete fakeEvent;
}

void VView::middleMouseButtonRelease(QMouseEvent *event)
{
    QMouseEvent *fakeEvent = new QMouseEvent(event->type(),event->localPos(),event->screenPos(),
                                             Qt::LeftButton, event->buttons() | Qt::LeftButton ,event->modifiers());
    QGraphicsView::mouseReleaseEvent(fakeEvent);
    this->setDragMode(QGraphicsView::RubberBandDrag);

    delete fakeEvent;
}

void VView::leftMouseButtonPress(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    QPoint pos = event->pos();
    QPointF obj_pos = mapToScene(pos);

    for(int i=0;i<this->_nodes.length();i++){
        if(this->_nodes[i]->getDesc()->contains(obj_pos)){

            // 如果选中了output socket，则产生虚拟连线
            for(int j=0;j<this->_nodes[i]->getOutputSocketNumber();j++){
                if(this->_nodes[i]->getDesc()->getOutputSockets()[j]->contains(obj_pos)){
                    // qDebug()<<"Click: OutSocket:"<<this->nodes[i]->index<<">"<<this->nodes[i]->desc->output_sockets[j]->index;
                    this->_edgeTemp = new VEdgeTemp(obj_pos,obj_pos);
                    this->_scene->addItem(_edgeTemp);
                    _isEdgeTempAlive = true;

                    this->_startNode = this->_nodes[i];
                    this->_startSocket = this->_nodes[i]->getDesc()->getOutputSockets()[j];

                    return;
                }
            }
            // 如果选中了input socket，则产生虚拟连线
            for(int j=0;j<this->_nodes[i]->getInputSocketNumber();j++){
                if(this->_nodes[i]->getDesc()->getInputSockets()[j]->contains(obj_pos)){
                    // qDebug()<<"Click: OutSocket:"<<this->nodes[i]->index<<">"<<this->nodes[i]->desc->input_sockets[j]->index;
                    this->_edgeTemp = new VEdgeTemp(obj_pos,obj_pos);
                    this->_scene->addItem(_edgeTemp);
                    _isEdgeTempAlive = true;

                    this->_endNode = this->_nodes[i];
                    this->_endSocket = this->_nodes[i]->getDesc()->getInputSockets()[j];

                    return;
                }
            }
        }
    }
}

void VView::LeftMouseButtonRelease(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if(_isEdgeTempAlive){
        this->_edgeTemp->hide();
        this->_scene->removeItem(this->_edgeTemp);
        _isEdgeTempAlive = false;
    }

    QPoint pos = event->pos();
    QPointF obj_pos = mapToScene(pos);

    for(int i=0;i<this->_nodes.length();i++){
        if(this->_nodes[i]->getDesc()->contains(obj_pos)){
            for(int j=0;j<this->_nodes[i]->getDesc()->getInputSockets().length();j++){
                if(this->_nodes[i]->getDesc()->getInputSockets()[j]->contains(obj_pos)){
                    this->_endNode = this->_nodes[i];
                    this->_endSocket = this->_nodes[i]->getDesc()->getInputSockets()[j];
                    addEdge(this->_startNode,this->_endNode,this->_startSocket,this->_endSocket);

                    this->_startNode = nullptr;
                    this->_endNode = nullptr;
                    this->_startSocket = nullptr;
                    this->_endSocket = nullptr;

                    return;
                }
            }
        }
    }
    for(int i=0;i<this->_nodes.length();i++){
        if(this->_nodes[i]->getDesc()->contains(obj_pos)){
            for(int j=0;j<this->_nodes[i]->getDesc()->getoutputSocketsLength();j++){
                if(this->_nodes[i]->getDesc()->getOutputSockets()[j]->contains(obj_pos)){
                    this->_startNode = this->_nodes[i];
                    this->_startSocket = this->_nodes[i]->getDesc()->getOutputSockets()[j];
                    addEdge(this->_startNode,this->_endNode,this->_startSocket,this->_endSocket);

                    this->_startNode = nullptr;
                    this->_endNode = nullptr;
                    this->_startSocket = nullptr;
                    this->_endSocket = nullptr;

                    return;
                }
            }
        }
    }
    this->_startNode = nullptr;
    this->_endNode = nullptr;
    this->_startSocket = nullptr;
    this->_endSocket = nullptr;
}

void VView::RightMouseButtonPress(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void VView::RightMouseButtonRelease(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void VView::addEdge(VNode *startNode, VNode *endNode, VSocket *startSocket, VSocket *endSocket)
{
    // 这里的input和output是相对edge的，不是相对node的
    if(startNode==nullptr ||endNode==nullptr ||
            startSocket==nullptr ||endSocket==nullptr){
        return;
    }
    if(startNode == endNode){
        qDebug()<<"Warning: you can not connect node to itself";
        return;
    }
    if(startSocket->getDataType() != endSocket->getDataType()){
        qDebug()<<"Warning: you can not connect Diff type data";
        return;
    }
    if(endSocket->getConnectedState()){
        qDebug()<<"Warning: this input socket had connected";
        return;
    }
    endSocket->setConnectedTrue();
    // 连线结束处的节点拥有新的输入
    endNode->addInputNode(startNode);
    // 连线开始处的节点拥有新的输出
    startNode->addOutputNode(endNode);

    // 该socket可以连接多个socket，记录了连接的socket的index

    this->_edge = new VEdge(startNode,endNode,
                              startSocket,endSocket);
    startNode->addOutputEdge(this->_edge);
    endNode->addInputEdge(this->_edge);


    this->_edge->setZValue(-1);
    this->_edges.append(this->_edge);
    this->_scene->addItem(this->_edge);

}

void VView::deleteItem()
{
    //qDebug()<<this->_scene->items().count();
    //qDebug()<<(item_list[i]->scene()==this->_scene);

    // 要删除的node列表
    QList<VNode*> node_list;
    for(int n=0;n<this->_nodes.length();n++){
        if(this->_nodes[n]->getDesc()->isSelected())
            node_list.append(this->_nodes[n]);
    }

    QList<VEdge*> temp_edges = _edges;
// TODO:优化两个数组比对
    for(int i=0;i<node_list.length();i++){
        // 删除节点相关的连线
        for(int j=0;j<temp_edges.length();j++){
            if(temp_edges[j]->_startNode == node_list[i] || temp_edges[j]->_endNode == node_list[i] ){
                // 如果某连线的连接节点是要删除的节点，则删除
                temp_edges[j]->_startNode->delInputEdge(temp_edges[j]);
                temp_edges[j]->_startNode->delOutputEdge(temp_edges[j]);
                temp_edges[j]->_endNode->delInputEdge(temp_edges[j]);
                temp_edges[j]->_endNode->delOutputEdge(temp_edges[j]);

                // 删除节点关系
                temp_edges[j]->_startNode->delOutputNode(temp_edges[j]->_endNode);
                temp_edges[j]->_endNode->delInputNode(temp_edges[j]->_startNode);
                // 更新socket状态
//                temp_edges[j]->_startSocket->is_connected = false;
                temp_edges[j]->_endSocket->setConnectedFalse();
                // 避免删除edge的渲染bug，先hide
                temp_edges[j]->hide();
                // 从Scene中移除
                this->_scene->removeItem(temp_edges[j]);
                // 从View内存中移除

                delete temp_edges[j];
                this->_edges.removeOne(temp_edges[j]);
                //temp_edges[j] = nullptr;
            }
        }
    }
    // 剩余的连线中判断是否要删除
    QList<VEdge*> edge_list;
    for(int n=0;n<this->_edges.length();n++){
        if(this->_edges[n]->isSelected())
            edge_list.append(this->_edges[n]);
    }
    for(int i=0;i<edge_list.length();i++){
        edge_list[i]->_startNode->delInputEdge(edge_list[i]);
        edge_list[i]->_startNode->delOutputEdge(edge_list[i]);
        edge_list[i]->_endNode->delInputEdge(edge_list[i]);
        edge_list[i]->_endNode->delOutputEdge(edge_list[i]);

        // 删除节点关系
        edge_list[i]->_startNode->delOutputNode(edge_list[i]->_endNode);
        edge_list[i]->_endNode->delInputNode(edge_list[i]->_startNode);

        // 更新socket状态
//        edge_list[i]->_startSocket->setConnectedFalse();
        edge_list[i]->_endSocket->setConnectedFalse();
        // 避免删除edge的渲染bug，先hide
        edge_list[i]->hide();
        // 从Scene中移除
        this->_scene->removeItem(edge_list[i]);
        // 从View内存中移除
        this->_edges.removeOne(edge_list[i]);
    }
    // 删除选中的节点
    for(int i=0;i<node_list.length();i++){
        this->_scene->removeItem(node_list[i]->getDesc());
        this->_nodes.removeOne(node_list[i]);
    }


    // 从内存中移除
    qDeleteAll(node_list);
    node_list.clear();
    qDeleteAll(edge_list);
    edge_list.clear();

    //qDebug()<<this->vapour_scene->items().count();
}

void VView::copyItem()
{

}

void VView::queryNodeInfo()
{

}

void VView::ergodicGraph()
{
//    _computeThread = new VComputeThread(this->_nodes);
//    _computeThread->start();

    qDebug()<<"Compute thread"<<QThread::currentThreadId();
    qDebug()<<"**************";
    QQueue<VNode*> queue;
    qDebug()<<"Compute Node init";
    for(int i=0;i<this->_nodes.length();i++){
        this->_nodes[i]->initData();
        this->_nodes[i]->inputVaild = this->_nodes[i]->getInputNodes().length();
        if(this->_nodes[i]->inputVaild == 0){
            queue.append(this->_nodes[i]);
        }
    }

    qDebug()<<"topological-sort start";
    while(!queue.empty()){
        qDebug()<<"Compute: "<<queue[0]->getIndex();
        queue[0]->handle();
        queue[0]->transfer();
        for(int k=0;k<queue[0]->getOutputNodes().length();k++){
            queue[0]->getOutputNodes()[k]->inputVaild--;
            if(queue[0]->getOutputNodes()[k]->inputVaild == 0){
                queue.append(queue[0]->getOutputNodes()[k]);
            }
        }
        queue.pop_front();
    }
    qDebug()<<"Compute Node Complete";
}

void VView::debugTest()
{

}

void VView::addNode(int index, QPoint pos)
{
    QPointF posF;
    pos = this->mapFromGlobal(pos);
    posF = this->mapToScene(pos);

    VNode* node = new VNodeNumber();
    //node->getDesc()->setDescWidth(160);
    posF.setX(posF.x()-40);
    posF.setY(posF.y()-40);
    node->setPos(posF);
    node->setIndex(index);
    node->setTitle(QString::number(index));
    this->_nodes.push_back(node);
    this->_scene->addItem(node->getDesc());
}

void VView::addNode(int index, int type, QPoint pos)
{
    QPointF posF;
    pos = this->mapFromGlobal(pos);
    posF = this->mapToScene(pos);
    VNode* node;

    switch(type){
    case 1 | VNodeTypeNumber:
        node = new VNodeNumber();
        break;
    case 2 | VNodeTypeNumberAdd:
        node = new VNodeNumberAdd();
        break;
    case 3 | VNodeTypeNumberSub:
        node = new VNodeNumberSub();
        break;
    case 4 | VNodeTypeNumberMul:
        node = new VNodeNumberMul();
        break;
    case 5 | VNodeTypeNumberDiv:
        node = new VNodeNumberDiv();
        break;

    case 6:
        node = new VNodeCvInput();
        break;
    case 7:
        node = new VNodeCvConvert();
        break;
    case 8:
        node = new VNodeCvThreshold();
        break;
    default:
        node = new VNodeNumber();
    }

    posF.setX(posF.x()-40);
    posF.setY(posF.y()-40);
    node->setPos(posF);
    node->setIndex(index);
    // node->setTitle(QString::number(index));
    this->_nodes.push_back(node);
    this->_scene->addItem(node->getDesc());
}

VNode* VView::addAndGetNode(int index, int type, QPoint pos)
{
    Q_UNUSED(index);
    Q_UNUSED(type);
    Q_UNUSED(pos);
    return {};
}
