#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    musicPlayer = new QMediaPlayer(this);
    connect(musicPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(musicPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);

    //setupList();          need to use library to setup list when the program starts. is library setup here?

    beginningDirectory = QDir::rootPath();
    QPixmap albumPic("C:\\Users\\steve\\Deezloader Music\\Ween\\Ween - The Mollusk\\cover.jpg");
    albumPic = albumPic.scaled(ui->albumCover->width(), ui->albumCover->height());
    ui->albumCover->setPixmap(albumPic);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete musicPlayer;
}

void MainWindow::on_actionAdd_Music_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Select Your Music", beginningDirectory);
    while(!files.empty())
    {
        std::string fileName = files.first().toStdString();
        new QListWidgetItem(tr(fileName.c_str()), ui->musicList);   //adds a new item on the list
        library.addSong(fileName);                                  //adds the song to the library
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

void MainWindow::on_musicList_itemDoubleClicked(QListWidgetItem *item)
{
    musicPlayer->setMedia(QUrl::fromLocalFile(item->text()));
    musicPlayer->setVolume(ui->volumeSlider->value());
    musicPlayer->play();

    ui->songPlayingLabel->setText(extractTitle(item->text().toStdString()));
}

void MainWindow::on_volumeSlider_sliderMoved(int position)
{
    musicPlayer->setVolume(position);
    int percent = (position * 100) / ui->volumeSlider->maximum();
    ui->volumePercent->setText(QString::fromStdString(std::to_string(percent)));
}

void MainWindow::on_songProgress_sliderMoved(int position)
{
    musicPlayer->setPosition(position);
}

void MainWindow::on_durationChanged(qint64 position)
{
    ui->songProgress->setMaximum(position);
}

void MainWindow::on_positionChanged(qint64 position)
{
    ui->songProgress->setValue(position);                   //move the song to the new position
    int seconds = position / 1000.0 + 0.5;                  //position is in milliseconds
    ui->positionLabel->setText(QString::number(seconds));
}

//void MainWindow::on_volumeChanged(int volume)
//{

//}

void MainWindow::on_pauseButton_clicked()
{
    musicPlayer->pause();
}

void MainWindow::on_playButton_clicked()
{
    musicPlayer->play();
}

QString MainWindow::extractTitle(std::string songLocation)
{
    std::ifstream songTxt(songLocation);
    std::string temp;
    QString songTitle="";
    std::getline(songTxt, temp);
    int titleStart = temp.find("TIT2");          //this is where the title is stored
    titleStart+=4;                               //skip 'TIT2'
    int titleEnd = temp.find("TPE1");
    songTitle = QString::fromStdString(temp.substr(titleStart, titleEnd-titleStart));
    while(songTitle.at(0).digitValue() != 65533)  //a character this value appears before the title
        songTitle.remove(0,1);
    songTitle.remove(0,1);                      //remove the extra character
    return songTitle;
}
