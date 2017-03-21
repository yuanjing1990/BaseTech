#include <string>
#include <vector>

#if defined(WIN32)
#include <io.h>
std::vector<std::string> dir(std::string dirName)
{
    std::vector<std::string> fileList;
    if(*dirName.rbegin() != '/' || *dirName.rbegin() != '\\') dirName.append("/");
    long hFile = 0;
    struct _finddata_t fileInfo;
    std::string fileName,exdName("*.xml");
    if((hFile = _findfirst(fileName.assign(dirName).append("\\*").c_str(),&fileInfo)) == -1)
        return fileList;
    do{
        fileList.push_back(dirName+fileInfo.name);
    }while(_findnext(hFile,&fileInfo) == 0);
    _findclose(hFile);
    return fileList;
}
#elif defined(LINUX)
#include <dirent.h>
std::vector<std::string> dir(std::string dirName)
{
    std::vector<std::string> fileList;
    if(*dirName.rbegin() != '/' || *dirName.rbegin() != '\\') dirName.append("/");
    DIR* dir = NULL;
    struct dirent *ptr = NULL;
    dir = opendir(dirName.c_str());
    while((ptr = readdir(dir)) != NULL)
    {
        fileList.push_back(dirName+ptr->d_name);
    }
    closedir(dir);
    return fileList;
}
#endif
