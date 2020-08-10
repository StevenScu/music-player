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
    for(unsigned int i = 0; i < albumList.size(); i++)
        albumList[i].clear();
    albumList.clear();
}

void LibraryInfo::addSong(std::string newSong)
{
    if(!songInFile(newSong))
    {
        SongInfo newSongInfo(extractSongTitle(newSong),extractAlbum(newSong),extractArtist(newSong), newSong, extractTrackNumber(newSong));
        int albumPosition = albumInLibrary(newSongInfo.getCoverLocation());
        if(albumPosition == -1)
            sortNewAlbum(newSongInfo);               //add the album to the list in alphabetical order
        else
            sortNewSong(newSongInfo, albumPosition); //add the song to the existing album, but sort it

        std::ofstream library;                                  //adding song to the file
        library.open("library.txt", std::ios::app);
        library << newSong << std::endl;
        library.close();
    }
}

unsigned int LibraryInfo::getSongCountInAlbum(unsigned int albumNumber)
{
    if(albumNumber <= albumList.size())
        return albumList[albumNumber].size();
    return 0;               //if that album number is invalid
}

unsigned int LibraryInfo::getAlbumCount()
{
    return albumList.size();
}

SongInfo LibraryInfo::getSongInfo(unsigned int albumNumber, unsigned int songNumber)
{
    if(albumNumber <= albumList.size() && songNumber <= albumList[albumNumber].size())
    {
        return albumList[albumNumber][songNumber];
    }
    return SongInfo();
}

SongInfo LibraryInfo::getSongInfoFromLocation(std::string songLocation)
{
    unsigned int numAlbums = getAlbumCount();
    for(unsigned int i = 0; i < numAlbums; i++)
    {
        unsigned int numSongs = getSongCountInAlbum(i);
        for(unsigned int j = 0; j < numSongs; j++)
        {
            if(albumList[i][j].getSongLocation() == songLocation)
                return albumList[i][j];
        }
    }
    return SongInfo();
}

std::vector<SongInfo> LibraryInfo::getAlbumFromAlbumTitle(std::string albumName)
{
    unsigned int numAlbums = getAlbumCount();
    for(unsigned int i = 0; i < numAlbums; i++)
    {
        if(albumList[i][0].getAlbum() == albumName)
            return albumList[i];
    }
    return std::vector<SongInfo>();
}

//Qt's list will save the songs by title only, so we will use that to get the SongInfo
SongInfo LibraryInfo::getSongInfoFromTitle(std::string songTitle)
{
    unsigned int numAlbums = getAlbumCount();
    for(unsigned int i = 0; i < numAlbums; i++)
    {
        unsigned int numSongs = getSongCountInAlbum(i);
        for(unsigned int j = 0; j < numSongs; j++)
        {
            if(albumList[i][j].getSongTitle() == songTitle)
                return albumList[i][j];
        }
    }
    return SongInfo();
}

void LibraryInfo::initializeLibrary(std::ifstream &library)
{
    std::string temp;
    while(std::getline(library, temp))                        //song title, album, artist, song location, song number
    {
        SongInfo newSongInfo(extractSongTitle(temp),extractAlbum(temp),extractArtist(temp), temp, extractTrackNumber(temp));
        int albumPosition = albumInLibrary(newSongInfo.getCoverLocation());
        if(albumPosition == -1)
            sortNewAlbum(newSongInfo);
        else
            sortNewSong(newSongInfo, albumPosition);
    }
}

//Creates a library file if it did not exist
void LibraryInfo::createDefaultLibrary()
{
    std::ofstream newLibrary;
    newLibrary.open("library.txt");
    newLibrary.close();
}

bool LibraryInfo::sortNewSong(SongInfo newSongInfo, int albumPosition)
{
    unsigned int newSongInfoTrackNumber = newSongInfo.getTrackNumber();
    for(unsigned int i = 0; i < albumList[albumPosition].size(); i++)
    {
        if(albumList[albumPosition][i].getTrackNumber() > newSongInfoTrackNumber)
        {
            albumList[albumPosition].insert(albumList[albumPosition].begin() + i, newSongInfo);
            return true;
        }
    }
    albumList[albumPosition].push_back(newSongInfo);
    return false;
}

bool LibraryInfo::sortNewAlbum(SongInfo newSongInfo)
{
    char firstLetterNewSongInfo = newSongInfo.getAlbum()[0];
    if(isalpha(firstLetterNewSongInfo))
        firstLetterNewSongInfo = toupper(firstLetterNewSongInfo);
    for(unsigned int i = 0; i < albumList.size(); i++)
    {
        char firstLetter = albumList[i][0].getAlbum()[0];
        if(isalpha(firstLetter))
            firstLetter = toupper(firstLetter);
        if(firstLetter > firstLetterNewSongInfo)
        {
            albumList.insert(albumList.begin() + i, {newSongInfo});
            return true;
        }
    }
    albumList.push_back({newSongInfo});
    return false;
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

//Returns the location of the album in the vector if that album is already in it
int LibraryInfo::albumInLibrary(std::string coverLocation)
{
    for(unsigned int i = 0; i < albumList.size(); i++)
    {
        if(albumList[i][0].getCoverLocation() == coverLocation)
            return i;
    }
    return -1;              //-1 says that the album is not in the albumList yet
}
