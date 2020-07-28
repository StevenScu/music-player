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
    unsigned int getSongCount();
    SongInfo getSongInfo(unsigned int songNumber);           //songNumber is useless unless looped through
    SongInfo getSongInfoFromLocation(std::string songLocation);
    SongInfo getSongInfoFromTitle(std::string songTitle);
    bool songInFile(std::string songPath);

private:
    std::vector<SongInfo> songList;
    void initializeLibrary(std::ifstream& library);
    void createDefaultLibrary();
};


#endif // LIBRARYINFO_H
