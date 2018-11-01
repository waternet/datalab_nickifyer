#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QFileDialog>
#include <QPixmap>
#include <QGraphicsPixmapItem>

const QString IMGPATH = "../img/";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->rbPositive, SIGNAL(clicked(bool)), ui->gvMain, SLOT(setPositive(bool)));

    ui->gvMain->setPositiveStupidFunction(ui->rbPositive->isChecked()); //quick and dirty..
    ui->gvMain->setOutputPath(QDir::currentPath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(const QString dir)
{
    m_img_files.clear();
    QDir directory(dir);
    QStringList filesList = directory.entryList(QDir::Files);
    QString fileName;

    foreach(fileName, filesList)
    {
        m_img_files.append(QDir(dir).filePath(fileName));
    }

    if(m_img_files.count()>0){
        m_current_index = 0;
        updateImage();
    }
}

void MainWindow::updateImage()
{
    ui->gvMain->showImage(m_img_files[m_current_index]);
}

void MainWindow::on_actionSelect_Directory_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ".",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    init(dir);
}

void MainWindow::on_btnNext_clicked()
{
    if(m_current_index<m_img_files.count()-1){
        m_current_index += 1;
        updateImage();
    }
}

void MainWindow::on_btnBack_clicked()
{
    if(m_current_index>0){
        m_current_index -= 1;
        updateImage();
    }
}

void MainWindow::on_btnFirst_clicked()
{
    if(m_img_files.count()>0){
        m_current_index = 0;
        updateImage();
    }
}

void MainWindow::on_btnLast_clicked()
{
    if(m_img_files.count()>0){
        m_current_index = m_img_files.count()-1;
        updateImage();
    }
}

void MainWindow::on_rbNegative_clicked()
{
    ui->gvMain->setPositive(false);
}
