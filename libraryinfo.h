#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <vector>
#include <iostream>
class LibraryInfo
{
public:
    LibraryInfo();
    ~LibraryInfo();
private:
    std::vector<std::string> songList;
};

#endif // LIBRARYINFO_H
