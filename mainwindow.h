#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMainWindow>
#include <QListWidget>
#include <QPixmap>
#include <string>
#include <iomanip>
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

    void on_musicList_itemDoubleClicked(QListWidgetItem *item);

    void on_volumeSlider_sliderMoved(int position);
    void on_songProgress_sliderMoved(int position);

    void on_durationChanged(qint64 position);
    void on_positionChanged(qint64 position);

    void on_pauseButton_clicked();

    void on_playButton_clicked();


    void on_actionQ_A_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *musicPlayer;
    LibraryInfo library;
    QString beginningDirectory;

    void setupList();
};

#endif // MAINWINDOW_H
