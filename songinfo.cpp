#include "songinfo.h"

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

std::string extractSongTitle(std::string songLocation)
{
    std::ifstream inFile;
    inFile.open(songLocation);

    std::string entireLine;
    std::string songTitle="";
    getline(inFile, entireLine);
    inFile.close();

    //Begin by looking for the 0xfe chacracter that marks text in mp3
    char check = 0xfe;
    while(entireLine.length()>1 && entireLine[0] != check)
        entireLine.erase(0,1);
    entireLine.erase(0,1);
    if(entireLine.find("TPE1") == -1)             //If this is not in the line, it is not the standard mp3 format
        return "[Title not found]";
    else
        entireLine = entireLine.substr(0, entireLine.find("TPE1"));

    //Remove all null characters
    unsigned int entireLineLength = entireLine.length();
    for(unsigned int i = 0; i < entireLineLength - 1; i++)
    {
        if(entireLine[i] != '\0')
            songTitle+=entireLine[i];
    }
    return songTitle;
}

std::string extractAlbum(std::string songLocation)
{
    std::string album;
    return album;
}

std::string extractTrackNumber(std::string songLocation)
{
    std::string trackNumber;
    return trackNumber;
}
