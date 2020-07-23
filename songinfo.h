#ifndef SONGINFO_H
#define SONGINFO_H

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

std::string extractSongTitle(std::string songLocation);
std::string extractAlbum(std::string songLocation);
std::string extractTrackNumber(std::string songLocation);


#endif // SONGINFO_H
