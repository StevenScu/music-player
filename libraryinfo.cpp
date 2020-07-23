#include "libraryinfo.h"

LibraryInfo::LibraryInfo()
{
    std::ifstream library;
    library.open("library.txt");
    if(library.fail())
        createDefaultLibrary();
    else
        initializeLibrary(library);
    library.close();
}

LibraryInfo::~LibraryInfo()
{
    songList.clear();
}

void LibraryInfo::addSong(std::string newSong)
{
    if(!songInFile(newSong))
    {
        songList.push_back({extractSongTitle(newSong),"","", newSong,0});         //MUST CHANGE

        std::ofstream library;                                  //adding song to the file
        library.open("library.txt", std::ios::app);
        library << newSong << std::endl;
        library.close();
    }
}

unsigned int LibraryInfo::getSongCount()
{
    return songList.size();
}

SongInfo LibraryInfo::getSongInfo(unsigned int songNumber)
{
    if(songNumber < songList.size())
        return songList[songNumber];
    return SongInfo();                               //return an empty song if none found
}

//Qt will save the songs by title only, so we will use that to get the cover location
SongInfo LibraryInfo::getSongInfoFromTitle(std::string songTitle)
{
    unsigned int songListSize = songList.size();
    for(unsigned int i = 0; i < songListSize; i++)
    {
        if(songList[i].getSongTitle() == songTitle)
            return songList[i];
    }
    return SongInfo();
}

void LibraryInfo::initializeLibrary(std::ifstream &library)
{
    std::string temp;
    while(std::getline(library, temp))                        //song title, album, artist, song location, song number
        songList.push_back({extractSongTitle(temp),"","", temp, 0});               //MUST CHANGE
}

//Creates a library file if it did not exist
void LibraryInfo::createDefaultLibrary()
{
    std::ofstream newLibrary;
    newLibrary.open("library.txt");
    newLibrary.close();
}

bool LibraryInfo::songInFile(std::string songPath)
{
    std::ifstream infile;
    infile.open("library.txt");
    if(infile.fail())
    {
        infile.close();
        return false;
    }
    std::string temp;
    while(std::getline(infile, temp))
    {
        if(temp == songPath)
        {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}
