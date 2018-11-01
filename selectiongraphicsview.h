#ifndef SELECTIONGRAPHICSVIEW_H
#define SELECTIONGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class SelectionGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SelectionGraphicsView(QWidget *parent = nullptr);

    void showImage(const QString filename);
    void setOutputPath(const QString path) {m_outputpath = path;}
    void setPositiveStupidFunction(const bool b) {m_positive=b;}

signals:

public slots:
    void setPositive(const bool b) {m_positive=b;}


protected:
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void mouseReleaseEvent(QMouseEvent *evt);

private:
    QPoint m_mousedown;
    QPoint m_mousecurrent;
    QGraphicsScene *m_scene;
    QGraphicsRectItem *m_selection_rect;
    QGraphicsPixmapItem *m_pixmap_item;
    QStringList m_image_list;
    QString m_image_path;
    QPixmap m_pixmap;
    QString m_outputpath;

    bool m_positive;
};

#endif // SELECTIONGRAPHICSVIEW_H
