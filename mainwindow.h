#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSelect_Directory_triggered();

    void on_btnNext_clicked();
    void on_btnBack_clicked();
    void on_btnFirst_clicked();
    void on_btnLast_clicked();
    void on_rbNegative_clicked();

private:
    Ui::MainWindow *ui;
    QList<QString> m_img_files;
    int m_current_index = -1;

    void init(const QString dir);

    void updateImage();


};

#endif // MAINWINDOW_H
