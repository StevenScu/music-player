#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <vector>
#include <iostream>
#include <fstream>

struct SongInfo
{
    SongInfo();
    SongInfo(std::string songTitle, std::string album, std::string artist, std::string songLocation, unsigned int trackNumber);
    std::string getSongTitle();
    std::string getAlbum();
    std::string getArtist();
    std::string getSongLocation();
    std::string getCoverLocation();    //uses songLocation to find
    unsigned int getTrackNumber();

private:
    std::string _songTitle;
    std::string _album;
    std::string _artist;
    std::string _songLocation;
    unsigned int _trackNumber;
};

class LibraryInfo
{
public:
    LibraryInfo();
    ~LibraryInfo();

    void addSong(std::string newSong);
    unsigned int getSongCount();
    SongInfo getSongInfo(unsigned int songNumber);           //songNumber is useless unless looped through
    SongInfo getSongInfoFromTitle(std::string songTitle);
    bool songInFile(std::string songPath);

private:
    std::vector<SongInfo> songList;
    void initializeLibrary(std::ifstream& library);
    void createDefaultLibrary();
};


#endif // LIBRARYINFO_H
