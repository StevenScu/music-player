#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMainWindow>
#include <QListWidget>
#include "libraryinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionAdd_Music_triggered();
    void on_actionChange_Default_Directory_triggered();
    void on_musicList_destroyed();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *musicPlayer;
    LibraryInfo *library;
    QString beginningDirectory;

};
#endif // MAINWINDOW_H
