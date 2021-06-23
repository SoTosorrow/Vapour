#include "vapour_view.h"

VapourView::VapourView(VapourScene* scene,QWidget *parent)
    :QGraphicsView(parent)
{
    qDebug()<<"Create: VapourView";
    this->vapour_scene = scene;

    this->setScene(this->vapour_scene);
    this->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing |
                         QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  // 防止画线的bug？
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet(" background: rgb(255,255,255);");

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse); //设置锚点
    this->setDragMode(QGraphicsView::RubberBandDrag);  // 框选

    //debug();
}

VapourView::~VapourView()
{
    delete vapour_scene;
    this->vapour_scene = nullptr;
}

void VapourView::addEdge(VapourNode *input_node, VapourNode *output_node,
                         VapourSocket *input_socket, VapourSocket *output_socket)
{
    // 这里的input和output是相对edge的，不是相对node的
    if(input_node==nullptr ||output_node==nullptr ||
            input_socket==nullptr ||output_socket==nullptr)
        return;
    if(input_node == output_node){
        qDebug()<<"Warning: you can not connect node to itself";
        return;
    }
    if(output_socket->is_connected==true){
        qDebug()<<"Warning: this input socket had connected";
        return;
    }
    output_socket->is_connected=true;
    // 连线结束处的节点拥有新的输入
    output_node->input_nodes.append(input_node);
    // 连线开始处的节点拥有新的输出
    input_node->output_nodes.append(output_node);
    // 该socket可以连接多个socket，记录了连接的socket的index

    // add connect_info
    QPair<int,int> a(input_socket->index,output_socket->index);
    QPair<VapourNode*,VapourNode*> n(input_node,output_node);
    QPair<QPair<VapourNode*,VapourNode*>,QPair<int,int>>t(n,a);
    input_node->connect_info.append(t);

    this->edge = new VapourEdge(input_node,output_node,
                              input_socket,output_socket);
    // update
    input_node->connect_edges.append(this->edge);
    input_node->output_edges.append(this->edge);
    output_node->input_edges.append(this->edge);

    this->edge->setZValue(-1);
    this->edges.append(this->edge);
    this->vapour_scene->addItem(this->edge);


}


/*
 * old deleteItem
void VapourView::deleteItem()
{
    //qDebug()<<this->editorScene->items().count();
    QList<QGraphicsItem*> item_list = this->vapour_scene->selectedItems();
    for(int i=0;i<item_list.length();i++){
        for(int j=0;j<this->nodes.length();j++){
            if(this->nodes[j]->desc == item_list[i]){
                //delete this->nodes[j];
                this->nodes.removeOne(this->nodes[j]);
                this->vapour_scene->removeItem(item_list[i]);
                continue;
            }
        }
        for(int j=0;j<this->edges.length();j++){
            if(this->edges[j] == item_list[i]){
                //qDebug()<<"judge"<<this->edges[j]->output_socket->index<<this->edges[j]->input_socket->index;
                QPair<int,int> a(this->edges[j]->input_socket->index,this->edges[j]->output_socket->index);
                QPair<VapourNode*,VapourNode*> n(this->edges[j]->input_node,this->edges[j]->output_node);
                QPair<QPair<VapourNode*,VapourNode*>,QPair<int,int>>t(n,a);
                this->edges[j]->input_node->connect_info.removeOne(t);

                this->edges[j]->input_node->output_nodes.removeOne(this->edges[j]->output_node);
                this->edges[j]->output_node->input_nodes.removeOne(this->edges[j]->input_node);
                this->edges[j]->input_socket->is_connected = false;
                this->edges[j]->output_socket->is_connected = false;
                //delete this->edges[j];

                this->edges[j]->hide();
                this->edges.removeOne(this->edges[j]);
                this->vapour_scene->removeItem(item_list[i]);
            }
        }
    }
    //qDebug()<<this->vapour_scene->items().count();

}
*/

// re-check
void VapourView::deleteItem()
{
    //qDebug()<<this->vapour_scene->items().count();
    //qDebug()<<(item_list[i]->scene()==this->vapour_scene);
    QList<VapourNode*> node_list;
    for(int n=0;n<this->nodes.length();n++){
        if(this->nodes[n]->getDesc()->isSelected())
            node_list.append(this->nodes[n]);
    }

    QList<VapourEdge*> temp_edges = edges;
    // TODO:优化两个数组比对
    for(int i=0;i<node_list.length();i++){
        // 删除节点相关的连线
        for(int j=0;j<temp_edges.length();j++){
            if(temp_edges[j]->input_node == node_list[i] || temp_edges[j]->output_node == node_list[i] ){
                // 如果某连线的连接节点是要删除的节点，则删除
                QPair<int,int> a(temp_edges[j]->input_socket->index,temp_edges[j]->output_socket->index);
                QPair<VapourNode*,VapourNode*> n(temp_edges[j]->input_node,temp_edges[j]->output_node);
                QPair<QPair<VapourNode*,VapourNode*>,QPair<int,int>>t(n,a);
                temp_edges[j]->input_node->connect_info.removeOne(t);

                // update
                temp_edges[j]->input_node->connect_edges.removeOne(temp_edges[j]);
                temp_edges[j]->output_node->connect_edges.removeOne(temp_edges[j]);
                temp_edges[j]->input_node->output_edges.removeOne(temp_edges[j]);
                temp_edges[j]->output_node->input_edges.removeOne(temp_edges[j]);


                // 删除节点关系
                temp_edges[j]->input_node->output_nodes.removeOne(temp_edges[j]->output_node);
                temp_edges[j]->output_node->input_nodes.removeOne(temp_edges[j]->input_node);
                // 更新socket状态
                temp_edges[j]->input_socket->is_connected = false;
                temp_edges[j]->output_socket->is_connected = false;
                // 避免删除edge的渲染bug，先hide
                temp_edges[j]->hide();
                // 从Scene中移除
                this->vapour_scene->removeItem(temp_edges[j]);
                // 从View内存中移除

                delete temp_edges[j];
                this->edges.removeOne(temp_edges[j]);
                //temp_edges[j] = nullptr;
            }
        }
    }
    // 剩余的连线中判断是否要删除
    QList<VapourEdge*> edge_list;
    for(int n=0;n<this->edges.length();n++){
        if(this->edges[n]->isSelected())
            edge_list.append(this->edges[n]);
    }
    for(int i=0;i<edge_list.length();i++){
        //qDebug()<<"judge"<<this->edges[j]->output_socket->index<<this->edges[j]->input_socket->index;
        QPair<int,int> a(edge_list[i]->input_socket->index,edge_list[i]->output_socket->index);
        QPair<VapourNode*,VapourNode*> n(edge_list[i]->input_node,edge_list[i]->output_node);
        QPair<QPair<VapourNode*,VapourNode*>,QPair<int,int>>t(n,a);
        edge_list[i]->input_node->connect_info.removeOne(t);

        // update
        edge_list[i]->input_node->connect_edges.removeOne(edge_list[i]);
        edge_list[i]->output_node->connect_edges.removeOne(edge_list[i]);
        edge_list[i]->input_node->output_edges.removeOne(edge_list[i]);
        edge_list[i]->output_node->input_edges.removeOne(edge_list[i]);


        // 删除节点关系
        edge_list[i]->input_node->output_nodes.removeOne(edge_list[i]->output_node);
        edge_list[i]->output_node->input_nodes.removeOne(edge_list[i]->input_node);
        // 更新socket状态
        edge_list[i]->input_socket->is_connected = false;
        edge_list[i]->output_socket->is_connected = false;
        // 避免删除edge的渲染bug，先hide
        edge_list[i]->hide();
        // 从Scene中移除
        this->vapour_scene->removeItem(edge_list[i]);
        // 从View内存中移除
        this->edges.removeOne(edge_list[i]);
    }
    // 删除选中的节点
    for(int i=0;i<node_list.length();i++){
        this->vapour_scene->removeItem(node_list[i]->desc);
        this->nodes.removeOne(node_list[i]);
    }


    // 从内存中移除
    qDeleteAll(node_list);
    node_list.clear();
    qDeleteAll(edge_list);
    edge_list.clear();

    //qDebug()<<this->vapour_scene->items().count();

}

void VapourView::copyNode()
{
    qDebug()<<"Copy";
    QList<VapourNode*> temp_nodes;
    for(int i=0;i<nodes.length();i++){
        if(nodes[i]->getDesc()->isSelected()){
            temp_nodes.append(nodes[i]);
            nodes[i]->getDesc()->setSelected(false);
        }
    }
    for(int i=0;i<temp_nodes.length();i++){
        // QPointF pos = temp_nodes[i]->getDesc()->getPos();
        QPoint node_pos = temp_nodes[i]->getDesc()->pos().toPoint();
        node_pos = mapFromParent(node_pos);
        QPoint pos = this->cursor().pos() + node_pos;
        VapourNode* temp_node = addAndGetNode(number++,temp_nodes[i]->getType(),pos);
        temp_node->getDesc()->setSelected(true);

    }
    // TODO copy edge
}




void VapourView::queryNodeInfo()
{
    QList<QGraphicsItem*> item_list = this->vapour_scene->selectedItems();
    for(int i=0;i<item_list.length();i++){
        for(int j=0;j<nodes.length();j++){
            if(nodes[j]->desc==item_list[i]){
                for(int n=0;n<nodes[j]->connect_info.length();n++){
                    qDebug()<<nodes[j]->index<<nodes[j]->connect_info[n].first.first->index<<
                              nodes[j]->connect_info[n].first.second->index<<
                              nodes[j]->connect_info[n].second.first<<nodes[j]->connect_info[n].second.second;
                    qDebug()<<nodes[j]->input_datas.length()<<nodes[j]->output_datas.length();
                }
            }
        }
    }
}

void VapourView::ergodicGraph()
{
    vapour_compute_thread = new VapourComputeThread(this->nodes);
    vapour_compute_thread->start();
    /*
    qDebug()<<"**************";
    QQueue<VapourNode*> queue;
    for(int i=0;i<this->nodes.length();i++){
        this->nodes[i]->initData();
        //for(int j=0;j<this->nodes[i]->input_nodes.length();j++)
        this->nodes[i]->input_vaild = this->nodes[i]->input_nodes.length();
        this->nodes[i]->output_vaild = this->nodes[i]->output_nodes.length();
        if(this->nodes[i]->input_vaild == 0){
            queue.append(this->nodes[i]);
        }
    }

    qDebug()<<"topological-sort";
    while(!queue.empty()){
        qDebug()<<"compute: "<<queue[0]->index;
        queue[0]->handle();
        queue[0]->transfer();
        for(int k=0;k<queue[0]->output_nodes.length();k++){
            queue[0]->output_nodes[k]->input_vaild--;
            if(queue[0]->output_nodes[k]->input_vaild == 0){
                queue.append(queue[0]->output_nodes[k]);
            }
        }
        queue.pop_front();
    }
    */
    //qDebug()<<"Compute Node Complete";
    //qDebug()<<"Main thread"<<QThread::currentThreadId();

}

void VapourView::debug()
{
    VapourNode* temp =new VapourNode();
    temp->desc->setDescWidth(200);
    VapourNode* temp2 = new VapourNode();
    temp2->desc->setDescWidth(200);
    this->nodes.append(temp);
    this->nodes.append(temp2);
    this->vapour_scene->addItem(temp->desc);
    this->vapour_scene->addItem(temp2->desc);

}

void VapourView::addNode(int index, QPoint pos)
{
    QPointF posF;
    pos = this->mapFromGlobal(pos);
    posF = this->mapToScene(pos);

    VapourNode* node = new VapourNodeInput();
    node->desc->setDescWidth(200);
    posF.setX(posF.x()-40);
    posF.setY(posF.y()-40);
    node->setPos(posF);
    node->setIndex(index);
    node->setTitle(QString::number(index));
    this->nodes.push_back(node);
    this->vapour_scene->addItem(node->desc);
}

void VapourView::addNode(int index, int type, QPoint pos)
{
    QPointF posF;
    pos = this->mapFromGlobal(pos);
    posF = this->mapToScene(pos);
    VapourNode* node;

    switch(type){
    case 0 | VapourNodeTypeInput:
        node = new VapourNodeInput();
        break;
    case 1 | VapourNodeTypeOutput:
        node = new VapourNodeOutput();
        node->getDesc()->setDescWidth(150);
        break;
    case 2 | VapourNodeTypeAdd:
        node = new VapourNodeAdd();
        node->getDesc()->setDescWidth(200);
        break;
    case 3 | VapourNodeTypeSub:
        node = new VapourNodeSub();
        node->getDesc()->setDescWidth(200);
        break;
    case 4 | VapourNodeTypeMul:
        node = new VapourNodeMul();
        node->getDesc()->setDescWidth(200);
        break;
    case 5 | VapourNodeTypeDiv:
        node = new VapourNodeDiv();
        node->getDesc()->setDescWidth(200);
        break;
    case 10:
        node = new VapourNodeCvInput();
        node->getDesc()->setDescWidth(200);
        node->getDesc()->setDescHeight(100);
        break;
    case 11:
        node = new VapourNodeCvAdd();
        node->getDesc()->setDescWidth(200);
        node->getDesc()->setDescHeight(200);
        break;
    case 12:
        node = new VapourNodeCvThreshold();
        node->getDesc()->setDescWidth(200);
        node->getDesc()->setDescHeight(170);
        break;
    case 13:
        node = new VapourNodeCvConvert();
        node->getDesc()->setDescWidth(200);
        node->getDesc()->setDescHeight(100);
        break;
    default:
        node = new VapourNodeInput();

    }

    posF.setX(posF.x()-40);
    posF.setY(posF.y()-40);
    node->setPos(posF);
    node->setIndex(index);
    // node->setTitle(QString::number(index));
    this->nodes.push_back(node);
    this->vapour_scene->addItem(node->desc);
}

VapourNode *VapourView::addAndGetNode(int index, int type, QPoint pos)
{
    QPointF posF;
    pos = this->mapFromGlobal(pos);
    posF = this->mapToScene(pos);
    VapourNode* node;

    switch(type){
    case 0 | VapourNodeTypeInput:
        node = new VapourNodeInput();
        break;
    case 1 | VapourNodeTypeOutput:
        node = new VapourNodeOutput();
        node->getDesc()->setDescWidth(150);
        break;
    case 2 | VapourNodeTypeAdd:
        node = new VapourNodeAdd();
        node->getDesc()->setDescWidth(200);
        break;
    case 3 | VapourNodeTypeSub:
        node = new VapourNodeSub();
        node->getDesc()->setDescWidth(200);
        break;
    case 4 | VapourNodeTypeMul:
        node = new VapourNodeMul();
        node->getDesc()->setDescWidth(200);
        break;
    case 5 | VapourNodeTypeDiv:
        node = new VapourNodeDiv();
        node->getDesc()->setDescWidth(200);
        break;
    case 10:
        node = new VapourNodeCvInput();
        node->getDesc()->setDescWidth(200);
        node->getDesc()->setDescHeight(100);
        break;
    case 11:
        node = new VapourNodeCvAdd();
        node->getDesc()->setDescWidth(200);
        node->getDesc()->setDescHeight(200);
        break;
    case 12:
        node = new VapourNodeCvThreshold();
        node->getDesc()->setDescWidth(200);
        node->getDesc()->setDescHeight(170);
        break;
    case 13:
        node = new VapourNodeCvConvert();
        node->getDesc()->setDescWidth(200);
        node->getDesc()->setDescHeight(100);
        break;
    default:
        node = new VapourNodeInput();

    }

    posF.setX(posF.x()-40);
    posF.setY(posF.y()-40);
    node->setPos(posF);
    node->setIndex(index);
    // node->setTitle(QString::number(index));
    this->nodes.push_back(node);
    this->vapour_scene->addItem(node->desc);
    return node;
}


void VapourView::keyPressEvent(QKeyEvent *event){
    QPoint pos = this->cursor().pos();
    if((event->modifiers()== Qt::ShiftModifier) && event->key() == Qt::Key_A){
        addNode(number++,pos);
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
        copyNode();
        return;
    }

    QGraphicsView::keyPressEvent(event);
}

void VapourView::mousePressEvent(QMouseEvent *event){
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

void VapourView::mouseReleaseEvent(QMouseEvent *event){
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
void VapourView::mouseMoveEvent(QMouseEvent *event)
{
    if(is_edge_temp_alive){
        QPointF pos = mapToScene(event->pos());

        this->edge_temp->setEndPos(pos);
        this->vapour_scene->update();
    }
    QGraphicsView::mouseMoveEvent(event);
}
void VapourView::middleMouseButtonPress(QMouseEvent *event){
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

void VapourView::middleMouseButtonRelease(QMouseEvent *event){
    QMouseEvent *fakeEvent = new QMouseEvent(event->type(),event->localPos(),event->screenPos(),
                                             Qt::LeftButton, event->buttons() | Qt::LeftButton ,event->modifiers());
    QGraphicsView::mouseReleaseEvent(fakeEvent);
    this->setDragMode(QGraphicsView::RubberBandDrag);

    delete fakeEvent;
}
void VapourView::leftMouseButtonPress(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    QPoint pos = event->pos();
    QPointF obj_pos = mapToScene(pos);

    for(int i=0;i<this->nodes.length();i++){
        if(this->nodes[i]->desc->contains(obj_pos)){

            // 如果选中了output socket，则产生虚拟连线
            for(int j=0;j<this->nodes[i]->output_socket_number;j++){
                if(this->nodes[i]->desc->output_sockets[j]->contains(obj_pos)){
                    // qDebug()<<"Click: OutSocket:"<<this->nodes[i]->index<<">"<<this->nodes[i]->desc->output_sockets[j]->index;
                    this->edge_temp = new VapourEdgeTemp(obj_pos,obj_pos);
                    this->vapour_scene->addItem(edge_temp);
                    is_edge_temp_alive = true;

                    this->start_node = this->nodes[i];
                    this->start_socket = this->nodes[i]->desc->output_sockets[j];

                    return;
                }
            }
            // 如果选中了input socket，则产生虚拟连线
            for(int j=0;j<this->nodes[i]->input_socket_number;j++){
                if(this->nodes[i]->desc->input_sockets[j]->contains(obj_pos)){
                    // qDebug()<<"Click: OutSocket:"<<this->nodes[i]->index<<">"<<this->nodes[i]->desc->input_sockets[j]->index;
                    this->edge_temp = new VapourEdgeTemp(obj_pos,obj_pos);
                    this->vapour_scene->addItem(edge_temp);
                    is_edge_temp_alive = true;

                    this->end_node = this->nodes[i];
                    this->end_socket = this->nodes[i]->desc->input_sockets[j];

                    return;
                }
            }
        }
    }


}

//TODO 增加连线模式以无需任何release都计算是否连线
void VapourView::LeftMouseButtonRelease(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if(is_edge_temp_alive){
        this->edge_temp->hide();
        this->vapour_scene->removeItem(this->edge_temp);
        is_edge_temp_alive = false;
    }

    QPoint pos = event->pos();
    QPointF obj_pos = mapToScene(pos);

    for(int i=0;i<this->nodes.length();i++){
        if(this->nodes[i]->desc->contains(obj_pos)){
            for(int j=0;j<this->nodes[i]->desc->input_sockets.length();j++){
                if(this->nodes[i]->desc->input_sockets[j]->contains(obj_pos)){
                    this->end_node = this->nodes[i];
                    this->end_socket = this->nodes[i]->desc->input_sockets[j];
                    addEdge(this->start_node,this->end_node,this->start_socket,this->end_socket);

                    this->start_node = nullptr;
                    this->end_node = nullptr;
                    this->start_socket = nullptr;
                    this->end_socket = nullptr;

                    return;
                }
            }
        }
    }
    for(int i=0;i<this->nodes.length();i++){
        if(this->nodes[i]->desc->contains(obj_pos)){
            for(int j=0;j<this->nodes[i]->desc->output_sockets.length();j++){
                if(this->nodes[i]->desc->output_sockets[j]->contains(obj_pos)){
                    this->start_node = this->nodes[i];
                    this->start_socket = this->nodes[i]->desc->output_sockets[j];
                    addEdge(this->start_node,this->end_node,this->start_socket,this->end_socket);

                    this->start_node = nullptr;
                    this->end_node = nullptr;
                    this->start_socket = nullptr;
                    this->end_socket = nullptr;

                    return;
                }
            }
        }
    }
    this->start_node = nullptr;
    this->end_node = nullptr;
    this->start_socket = nullptr;
    this->end_socket = nullptr;




}
void VapourView::RightMouseButtonPress(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
void VapourView::RightMouseButtonRelease(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}
void VapourView::wheelEvent(QWheelEvent *event)
{
    // the factor of zoom
    float zoomOutFactor = 1 / this->zoomInFactor;
    float zoomFactor;
    // store the scene pos
    QPointF *oldPos = new QPointF(this->mapToScene(event->pos()));
    Q_UNUSED(oldPos);
    if(event->angleDelta().y() > 0){
        zoomFactor = zoomInFactor;
        zoom += zoomStep;
    }
    else{
        zoomFactor = zoomOutFactor;
        zoom -= zoomStep;
    }

    BOOLEAN clamped = false;  // 放缩的限制
    if(this->zoom < zoomRange[0]){
        this->zoom = zoomRange[0];
        clamped = true;
    }
    if(this->zoom > zoomRange[1]){
        this->zoom = zoomRange[1];
        clamped = true;
    }

    if(!clamped || !this->zoomClamp)
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

void VapourView::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    QPoint pos = this->cursor().pos();
    QPoint pos2 = this->mapFromGlobal(pos);
    pos2 = this->mapToGlobal(pos2);

    menu = new QMenu();
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

    menu->setStyleSheet(qss);


    qDeleteAll(action);
    action.clear();
    action.append(menu->addAction("DoubleInput"));
    connect(action[0], &QAction::triggered, [=]()
    {
        addNode(number++,0,pos);
    });
    action.append(menu->addAction("DoubleOutput"));
    connect(action[1], &QAction::triggered, [=]()
    {
        addNode(number++,1,pos);
    });
    action.append(menu->addAction("DoubleAdd"));
    connect(action[2], &QAction::triggered, [=]()
    {
        addNode(number++,2,pos);
    });
    action.append(menu->addAction("DoubleSub"));
    connect(action[3], &QAction::triggered, [=]()
    {
        addNode(number++,3,pos);
    });
    action.append(menu->addAction("DoubleMul"));
    connect(action[4], &QAction::triggered, [=]()
    {
        addNode(number++,4,pos);
    });
    action.append(menu->addAction("DoubleDiv"));
    connect(action[5], &QAction::triggered, [=]()
    {
        addNode(number++,5,pos);
    });
    menu->addSeparator();


    action.append(menu->addAction("ImageLoad"));
    connect(action[6], &QAction::triggered, [=]()
    {
        addNode(number++,10,pos);
    });
    action.append(menu->addAction("ImageBitwiseAnd"));
    connect(action[7], &QAction::triggered, [=]()
    {
        addNode(number++,11,pos);
    });
    action.append(menu->addAction("ImageThreshold"));
    connect(action[8], &QAction::triggered, [=]()
    {
        addNode(number++,12,pos);
    });
    action.append(menu->addAction("ImageConvert"));
    connect(action[9], &QAction::triggered, [=]()
    {
        addNode(number++,13,pos);
    });



    QMenu *funcMenu = new QMenu("Func");
    QAction *addNoden = funcMenu->addAction("JustAShow");
    Q_UNUSED(addNoden);

//    //addNoden->setMenu(childMenu);
    funcMenu->setStyleSheet(qss);
    menu->addMenu(funcMenu);
    menu->popup(pos);
    //menu->exec(QCursor::pos());



    // QAction *addNode1 = menu->addAction("原点Node");
    // connect(addNode1,SIGNAL(triggered()),this,SLOT(addNode()));
    // std::bind
    // connect(addNode2, &QAction::triggered, this, std::bind(addNode(), pos));
}
