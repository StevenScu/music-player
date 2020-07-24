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

std::string extractData(std::string songLocation, std::string sectionStart, std::string sectionEnd)
{
    std::ifstream inFile;
    inFile.open(songLocation);

    std::string entireLine;
    std::string wantedData="";
    getline(inFile, entireLine);
    inFile.close();

    //Remove the unneeded data before the data that will be displayed
    if(entireLine.find(sectionStart) == -1)
        return "[Song in unsupported format]";
    entireLine = entireLine.substr(entireLine.find(sectionStart));

    //Begin by looking for the 0xfe character that marks sections in mp3
    char check = 0xfe;
    while(entireLine.length()>1 && entireLine[0] != check)
        entireLine.erase(0,1);
    entireLine.erase(0,1);
    if(entireLine.find(sectionEnd) == -1)             //If this is not in the line, it is not the standard mp3 format
        return "[Song in unsupported format]";
    else
        entireLine = entireLine.substr(0, entireLine.find(sectionEnd));

    //Remove all null characters
    unsigned int entireLineLength = entireLine.length();
    for(unsigned int i = 0; i < entireLineLength - 1; i++)
    {
        if(entireLine[i] != '\0')
            wantedData+=entireLine[i];
    }
    return wantedData;
}

std::string extractSongTitle(std::string songLocation)
{
    return extractData(songLocation, "TIT2", "TPE1");   //the title is marked by TIT2. the next section is marked by TPE1
}

std::string extractArtist(std::string songLocation)
{
    //Artists are between TPE1 and TXXX OR A R T I S T S and TALB
    return extractData(songLocation, "TPE1", "TXXX");
}

std::string extractAlbum(std::string songLocation)
{
    return extractData(songLocation, "TALB", "TPE2");
}

unsigned int extractTrackNumber(std::string songLocation)
{
    std::string trackNumberString = extractData(songLocation, "TRCK", "TPOS");
    if(trackNumberString[0] == '[')
        return 0;
    return stoi(trackNumberString);
}
