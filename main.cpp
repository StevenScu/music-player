/**
  Issues:
  1. Not include duplicate songs
  2. Play songs that will not currently open (codec issues)
  3. Time Elapsed should be in HH:MM:SS format
  4. Rename the main window from MainWindow
  5. Need copy contructors and overwriting the assignment operator
  6. Show song info under album cover
  7. Read MP3 data and store it properly in SongInfo objects
  8. Display song names in the list, not the paths

  Features To Add:
  1. Autoplay next song in album
  2. Add a dark mode
  3. Make it resizeable or lock it this size
  4. Add a help option on the menu that has a Q&A

  */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
