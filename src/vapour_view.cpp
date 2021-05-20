#include "vapour_view.h"

VapourView::VapourView(VapourScene* scene,QWidget *parent)
    :QGraphicsView(parent)
{
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

    debug();
}

VapourView::~VapourView()
{
    delete vapour_scene;
    this->vapour_scene = nullptr;
}

void VapourView::debug()
{
    this->vapour_scene->addItem(new VapourDescriptor("test"));
}
