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
    songList.push_back({newSong,"","", newSong});           //MUST CHANGE

    std::ofstream library;                                  //adding song to the file
    library.open("library.txt", std::ios::app);
    library << newSong << std::endl;
    library.close();
}

void LibraryInfo::initializeLibrary(std::ifstream &library)
{
    std::string temp;
    while(std::getline(library, temp))                        //song title, album, artist, song location
        songList.push_back({temp,"","", temp});               //MUST CHANGE
}

//Creates a library file if it did not exist
void LibraryInfo::createDefaultLibrary()
{
    std::ofstream newLibrary;
    newLibrary.open("library.txt");
    newLibrary.close();
}

SongInfo::SongInfo(std::string songTitle, std::string album, std::string artist, std::string songLocation)
{
    _songTitle = songTitle;
    _album = album;
    _artist = artist;
    _songLocation = songLocation;
}

std::string SongInfo::getSongTitle()
{
    return _songTitle;
}

std::string SongInfo::getAlbum()
{
    return  _album;
}

std::string SongInfo::getArtist()
{
    return _artist;
}

std::string SongInfo::getSongLocation()
{
    return _songLocation;
}

std::string SongInfo::getCoverLocation()
{
    std::string coverLocation = _songLocation;
    while(coverLocation[coverLocation.length()-1] != '\\')
        coverLocation.pop_back();
    coverLocation += "cover.jpg";
    return coverLocation;
}
