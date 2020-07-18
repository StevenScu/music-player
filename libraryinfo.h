#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <vector>
#include <iostream>
#include <fstream>

struct SongInfo
{
    SongInfo(std::string songTitle, std::string album, std::string artist, std::string songLocation);
    std::string getSongTitle();
    std::string getAlbum();
    std::string getArtist();
    std::string getSongLocation();
    std::string getCoverLocation();    //uses songLocation to find
private:
    std::string _songTitle;
    std::string _album;
    std::string _artist;
    std::string _songLocation;

};

class LibraryInfo
{
public:
    LibraryInfo();
    ~LibraryInfo();

    void addSong(std::string newSong);

private:
    std::vector<SongInfo> songList;
    void initializeLibrary(std::ifstream& library);
    void createDefaultLibrary();
};


#endif // LIBRARYINFO_H
