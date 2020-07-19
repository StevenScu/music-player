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
    songList.push_back({newSong,"","", newSong,0});           //MUST CHANGE

    std::ofstream library;                                  //adding song to the file
    library.open("library.txt", std::ios::app);
    library << newSong << std::endl;
    library.close();
}

unsigned int LibraryInfo::getSongCount()
{
    return songList.size();
}

SongInfo LibraryInfo::getSongInfo(unsigned int songNumber)
{
    if(songNumber < songList.size() && songNumber >= 0)
        return songList[songNumber];
    return SongInfo();                               //return an empty song if none found
}

//Qt will save the songs by title only, so we will use that to get the cover location
std::string LibraryInfo::getCoverLocationFromTitle(std::string songTitle)
{
    for(unsigned int i = 0; i < songList.size(); i++)
    {
        if(songList[i].getSongTitle() == songTitle)
            return songList[i].getCoverLocation();
    }
    return "";
}

void LibraryInfo::initializeLibrary(std::ifstream &library)
{
    std::string temp;
    while(std::getline(library, temp))                        //song title, album, artist, song location
        songList.push_back({temp,"","", temp, 0});               //MUST CHANGE
}

//Creates a library file if it did not exist
void LibraryInfo::createDefaultLibrary()
{
    std::ofstream newLibrary;
    newLibrary.open("library.txt");
    newLibrary.close();
}

SongInfo::SongInfo()
{
    _songTitle = "Title";
    _album = "Album";
    _artist = "Artist";
    _songLocation = "Song Location";
    _trackNumber = 0;
}

SongInfo::SongInfo(std::string songTitle, std::string album, std::string artist,
                   std::string songLocation, unsigned int trackNumber)
{
    _songTitle = songTitle;
    _album = album;
    _artist = artist;
    _songLocation = songLocation;
    _trackNumber = trackNumber;
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

unsigned int SongInfo::getTrackNumber()
{
    return _trackNumber;
}

std::string SongInfo::getCoverLocation()
{
    std::string coverLocation = _songLocation;
    //Remove the song's info in the file path
    while(coverLocation[coverLocation.length()-1] != '/')
        coverLocation.pop_back();
    coverLocation += "cover.jpg";
    return coverLocation;
}
