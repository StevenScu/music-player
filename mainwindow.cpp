#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    musicPlayer = new QMediaPlayer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_File_triggered()
{
    //QMessageBox::information(this, "Message", "Button was clicked!", QMessageBox::Ok);
    //file_name will hold the path of the file
    QString file_name = QFileDialog::getOpenFileName(this, "Choose Your Music File", "C://");
}
