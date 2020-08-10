#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <vector>

#include "songinfo.h"

class LibraryInfo
{
public:
    LibraryInfo();
    ~LibraryInfo();

    void addSong(std::string newSong);
    unsigned int getSongCountInAlbum(unsigned int albumNumber);
    unsigned int getAlbumCount();
    SongInfo getSongInfo(unsigned int albumNumber, unsigned int songNumber); //used when looping through every song
    SongInfo getSongInfoFromTitle(std::string songTitle);
    SongInfo getSongInfoFromLocation(std::string songLocation);
    std::vector<SongInfo> getAlbumFromAlbumTitle(std::string albumName);
    bool songInFile(std::string songPath);
    int albumInLibrary(std::string coverLocation); //each song in an album will share a cover location (AKA be in the same folder)

private:
    //std::vector<SongInfo> songList;
    std::vector<std::vector<SongInfo>> albumList;
    void initializeLibrary(std::ifstream& library);
    void createDefaultLibrary();
    bool sortNewSong(SongInfo newSongInfo, int albumPosition);
    bool sortNewAlbum(SongInfo newSongInfo);
};


#endif // LIBRARYINFO_H
