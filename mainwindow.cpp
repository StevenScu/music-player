#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    musicPlayer = new QMediaPlayer(this);
    beginningDirectory = "C://";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete musicPlayer;
    delete library;
}

void MainWindow::on_actionAdd_Music_triggered()
{
    //QMessageBox::information(this, "Message", "Button was clicked!", QMessageBox::Ok);
    QStringList files = QFileDialog::getOpenFileNames(this, "Select Your Music", beginningDirectory);
    while(!files.empty())
    {
        new QListWidgetItem(tr(files.first().toStdString().c_str()), ui->musicList);
        files.pop_front();
    }
}

void MainWindow::on_actionChange_Default_Directory_triggered()
{
    beginningDirectory = QFileDialog::getExistingDirectory(this, "Choose a Default Directory", beginningDirectory);
}

void MainWindow::on_musicList_destroyed()
{
    while(!ui->musicList->size().isEmpty())
    {
        delete ui->musicList->item(0);
        ui->musicList->removeItemWidget(ui->musicList->item(0));
    }
}
