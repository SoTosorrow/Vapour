#include "editor_view.h"

EditorView::EditorView(EditorScene* scene,QWidget *parent)
    :QGraphicsView(parent)
{
    // for unique_ptr
    // this->editorScene = std::move(scene);
    this->editorScene = scene;

    this->setScene(this->editorScene);
    this->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing |
                         QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  // 防止画线的bug？
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse); //设置锚点
    this->setDragMode(QGraphicsView::RubberBandDrag);  // 框选


}
EditorView::~EditorView()
{
    delete editorScene;
    this->editorScene = nullptr;
    delete menu;
    this->menu = nullptr;
}
void EditorView::keyPressEvent(QKeyEvent *event){
    QPoint pos = this->cursor().pos();
    if((event->modifiers()== Qt::ShiftModifier) && event->key() == Qt::Key_A){
        this->addNode(number++,pos);
        return;
    }

    QGraphicsView::keyPressEvent(event);
}

void EditorView::mousePressEvent(QMouseEvent *event){
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

void EditorView::mouseReleaseEvent(QMouseEvent *event){
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
void EditorView::mouseMoveEvent(QMouseEvent *event)
{
    if(is_edge_temp_alive){
        QPointF pos = mapToScene(event->pos());

        this->edge_temp->setEndPos(pos);
        this->editorScene->update();
    }
    QGraphicsView::mouseMoveEvent(event);
}
void EditorView::middleMouseButtonPress(QMouseEvent *event){
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

void EditorView::middleMouseButtonRelease(QMouseEvent *event){
    QMouseEvent *fakeEvent = new QMouseEvent(event->type(),event->localPos(),event->screenPos(),
                                             Qt::LeftButton, event->buttons() | Qt::LeftButton ,event->modifiers());
    QGraphicsView::mouseReleaseEvent(fakeEvent);
    this->setDragMode(QGraphicsView::RubberBandDrag);

    delete fakeEvent;
}
void EditorView::leftMouseButtonPress(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    QPoint pos = event->pos();
    QPointF obj_pos = mapToScene(pos);

    for(int i=0;i<this->nodes.length();i++){
        if(this->nodes[i]->item->contains(obj_pos)){

            // 如果选中了output socket，则产生虚拟连线
            for(int j=0;j<this->nodes[i]->output_socket_number;j++){
                if(this->nodes[i]->output_sockets[j]->contains(obj_pos)){
                    qDebug()<<"Click: OutSocket:"<<this->nodes[i]->index<<">"<<this->nodes[i]->output_sockets[j]->index;
                    this->edge_temp = new NodeEdgeTemp(obj_pos,obj_pos);
                    this->editorScene->addItem(edge_temp);
                    is_edge_temp_alive = true;

                    this->start_node = this->nodes[i];
                    this->start_socket = this->nodes[i]->output_sockets[j];

                    return;
                }
            }
            // 如果选中了input socket，则产生虚拟连线
            for(int j=0;j<this->nodes[i]->input_socket_number;j++){
                if(this->nodes[i]->input_sockets[j]->contains(obj_pos)){
                    qDebug()<<"Click: OutSocket:"<<this->nodes[i]->index<<">"<<this->nodes[i]->input_sockets[j]->index;
                    this->edge_temp = new NodeEdgeTemp(obj_pos,obj_pos);
                    this->editorScene->addItem(edge_temp);
                    is_edge_temp_alive = true;

                    this->end_node = this->nodes[i];
                    this->end_socket = this->nodes[i]->input_sockets[j];

                    return;
                }
            }
        }
    }


}

//TODO 增加连线模式以无需任何release都计算是否连线
void EditorView::LeftMouseButtonRelease(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if(is_edge_temp_alive){
        this->edge_temp->hide();
        this->editorScene->removeItem(this->edge_temp);
        is_edge_temp_alive = false;
    }

    QPoint pos = event->pos();
    QPointF obj_pos = mapToScene(pos);

    for(int i=0;i<this->nodes.length();i++){
        if(this->nodes[i]->item->contains(obj_pos)){
            for(int j=0;j<this->nodes[i]->input_sockets.length();j++){
                if(this->nodes[i]->input_sockets[j]->contains(obj_pos)){
                    this->end_node = this->nodes[i];
                    this->end_socket = this->nodes[i]->input_sockets[j];
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
        if(this->nodes[i]->item->contains(obj_pos)){
            for(int j=0;j<this->nodes[i]->output_sockets.length();j++){
                if(this->nodes[i]->output_sockets[j]->contains(obj_pos)){
                    this->start_node = this->nodes[i];
                    this->start_socket = this->nodes[i]->output_sockets[j];
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
void EditorView::RightMouseButtonPress(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
void EditorView::RightMouseButtonRelease(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void EditorView::addEdge(Node *input_node, Node *output_node,
                         NodeSocket *input_socket, NodeSocket *output_socket)
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
    this->edge = new NodeEdge(input_node,output_node,
                              input_socket,output_socket);
    this->edge->setZValue(-1);
    this->edges.append(this->edge);
    this->editorScene->addItem(this->edge);


}


void EditorView::addNode(int index,QPoint pos)
{
    QPointF posF;
    pos = this->mapFromGlobal(pos);
    posF = this->mapToScene(pos);

    Node* node = new Node();
    posF.setX(posF.x()-40);
    posF.setY(posF.y()-40);
    node->setPos(posF);
    node->setIndex(index);
    this->nodes.push_back(node);
    this->editorScene->addItem(node->item);


}

void EditorView::addNode()
{
    Node* node = new Node();
    this->nodes.push_back(node);
    this->editorScene->addItem(node->item);

}



void EditorView::buildGraph()
{

}
void EditorView::ergodicGraph()
{

}



void EditorView::wheelEvent(QWheelEvent *event)
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

void EditorView::contextMenuEvent(QContextMenuEvent *event)
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
                            ;}";
    menu->setStyleSheet(qss);

    QAction *addNode1 = menu->addAction("Test-Node");
    connect(addNode1, &QAction::triggered, [=]()
    {
        addNode(number++,pos);
    });
    menu->popup(pos);


    // QAction *addNode1 = menu->addAction("原点Node");
    // connect(addNode1,SIGNAL(triggered()),this,SLOT(addNode()));
    // std::bind
    // connect(addNode2, &QAction::triggered, this, std::bind(addNode(), pos));
}
