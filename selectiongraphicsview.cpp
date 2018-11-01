#include "selectiongraphicsview.h"
#include <QMouseEvent>
#include <QDateTime>
#include <QDir>

SelectionGraphicsView::SelectionGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    this->setParent(parent);
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    m_selection_rect = NULL;
    m_pixmap_item = NULL;
}

void SelectionGraphicsView::showImage(const QString filename)
{
    QImage *img = new QImage();
    img->load(filename);

    m_pixmap = QPixmap::fromImage(*img);
    if(m_pixmap_item==NULL){
        m_pixmap_item = m_scene->addPixmap(m_pixmap);
    }else{
        m_pixmap_item->setPixmap(m_pixmap);
    }
}

void SelectionGraphicsView::mousePressEvent(QMouseEvent *evt)
{
    m_mousedown = evt->pos();

    if(m_selection_rect==NULL){
        m_selection_rect = m_scene->addRect(m_mousedown.x(), m_mousedown.y(), 1, 1, QPen(Qt::black));;
    }else{
       m_selection_rect->setRect(m_mousedown.x(), m_mousedown.y(), 1, 1);
    }
}

void SelectionGraphicsView::mouseMoveEvent(QMouseEvent *evt)
{
    m_mousecurrent = evt->pos();
    if(m_selection_rect!=NULL){
        int w = m_mousecurrent.x() - m_mousedown.x();
        int h = m_mousecurrent.y() - m_mousedown.y();
        m_selection_rect->setRect(m_mousedown.x(), m_mousedown.y(), w, h);
    }

    update();
}

void SelectionGraphicsView::mouseReleaseEvent(QMouseEvent *evt)
{
    Q_UNUSED(evt);

    QString filename;
    if(m_positive){
        filename = "p_" + QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz") + ".jpg";
    }else{
        filename = "n_" + QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz") + ".jpg";
    }

    QPixmap pixmap;
    if (m_pixmap_item!=NULL){
        int w = m_mousecurrent.x() - m_mousedown.x();
        int h = m_mousecurrent.y() - m_mousedown.y();
        pixmap = m_pixmap.copy(m_mousedown.x(), m_mousedown.y(), w, h);
    }

    QString finalname = QDir(m_outputpath).filePath(filename);
    pixmap.save(finalname, "JPG");

}
