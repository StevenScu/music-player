#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , library()           //need to read songs from the file so that we can add them in setupList
{
    ui->setupUi(this);
    musicPlayer = new QMediaPlayer(this);
    connect(musicPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(musicPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);

    musicPlaylist = new QMediaPlaylist;
    connect(musicPlaylist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::on_currentIndexChanged);

    setupList();

    beginningDirectory = QDir::rootPath();

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
        if(!library.songInFile(fileName))
        {
            library.addSong(fileName);  //adds the song to the library
            ui->musicList->clear();     //will remake list with new song (to sort and add new albums)
            setupList();                //simply re-displays the songs; does not go back into files
        }
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
    //Need the song title. The list includes the song number too, so remove that
    std::string stringWithNumber = item->text().toStdString();
    std::string songTitle = stringWithNumber.substr(stringWithNumber.find(" ")).erase(0,1); //remove the number using the added space
    SongInfo currentSong = library.getSongInfoFromTitle(songTitle);

    //Add the songs from the selected album into the playlist
    musicPlaylist->clear();
    std::vector<SongInfo> album = library.getAlbumFromAlbumTitle(currentSong.getAlbum());
    unsigned int albumLength = album.size();
    for(unsigned int i = 0; i < albumLength; i++)
        musicPlaylist->addMedia(QUrl(QString::fromStdString(album[i].getSongLocation())));

    //Play the album at the selected song at the current volume
    musicPlayer->setPlaylist(musicPlaylist);
    musicPlaylist->setCurrentIndex(currentSong.getTrackNumber() - 1);       //index starts at 0
    musicPlayer->setVolume(ui->volumeSlider->value());
    musicPlayer->play();

    //Display the saved album cover
    QString coverLocation = QString::fromStdString(currentSong.getCoverLocation());
    QPixmap albumPic(coverLocation);
    albumPic = albumPic.scaled(ui->albumCover->width(), ui->albumCover->height());
    ui->albumCover->setPixmap(albumPic);

    //Put the song info under the album cover
    ui->songPlayingLabel->setText(QString::fromStdString(currentSong.getSongTitle()));
    ui->artistInfoLabel->setText(QString::fromStdString(currentSong.getArtist() + " - " + currentSong.getAlbum()));
}

void MainWindow::on_currentIndexChanged(int index)
{
    if(ui->songPlayingLabel->text() != "")              //This will be needed for the first song selected
    {
        //Get the new song based on the new index of the playlist
        SongInfo previousSong = library.getSongInfoFromTitle(ui->songPlayingLabel->text().toStdString());
        SongInfo thisSong = library.getAlbumFromAlbumTitle(previousSong.getAlbum())[index];

        //Change the song info to the new info
        //This will be in the same album, but the artist might differ, so must change
        ui->songPlayingLabel->setText(QString::fromStdString(thisSong.getSongTitle()));
        ui->artistInfoLabel->setText(QString::fromStdString(thisSong.getArtist() + " - " + thisSong.getAlbum()));
    }
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
    //Calculate the hours, minutes, and seconds elapsed into ints
    ui->songProgress->setValue(position);                   //move the song to the new position
    int elapsedTime = position / 1000.0 + 0.5;              //position is in milliseconds
    int seconds = elapsedTime % 60;
    int minutes = (elapsedTime / 60) % 60;                  //will display 0-59, then switch to 0 again
    int hours = elapsedTime / (60*60);                      //hours will grow for as long as needed

    //Convert these ints to QString so that we can display them
    QString finalDisplay = "";
    if(hours > 0)
        finalDisplay += QString::number(hours) + ":";
    QString minutesDisplay = QString::number(minutes);
    if(minutes < 10)                                        //always keep the time at a width of two (00)
        minutesDisplay = '0' + minutesDisplay;
    QString secondsDisplay = QString::number(seconds);
    if(seconds < 10)
        secondsDisplay = '0' + secondsDisplay;
    finalDisplay += minutesDisplay + ":" + secondsDisplay;

    ui->positionLabel->setText(finalDisplay);
}

void MainWindow::on_pauseButton_clicked()
{
    musicPlayer->pause();
}

void MainWindow::on_playButton_clicked()
{
    musicPlayer->play();
}

void MainWindow::setupList()
{
    unsigned int albumCount = library.getAlbumCount();
    for(unsigned int i = 0; i < albumCount; i++)
    {
        unsigned int songCount = library.getSongCountInAlbum(i);
        for(unsigned int j = 0; j < songCount; j++)
        {
            std::string itemToAdd = (std::to_string(library.getSongInfo(i,j).getTrackNumber()) + ". " + library.getSongInfo(i,j).getSongTitle());
            new QListWidgetItem(tr(itemToAdd.c_str()), ui->musicList);   //adds a new item on the list
        }
    }
}

void MainWindow::on_actionQ_A_triggered()
{
    QMessageBox messageBox;
    QString message = "Q: How do you add album art?\n"
                      "A: In the folder for that album, add a jpg called 'cover' that contains your art.\n\n"
                      "";
    messageBox.setText(message);
    messageBox.exec();
}
