#include <string>
#include <functional>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

bool isDirectory(const string &path)
{
    struct stat buffer;
    return (!path.empty() &&
            stat(path.c_str(), &buffer) == 0 &&
            (buffer.st_mode & S_IFDIR));
}

void listFilesRecusive(const string &path, std::function<void(const string&)> cb)
{
    DIR *dir = NULL;
    if ((dir = opendir(path.c_str())) != NULL) 
    {
        while (struct dirent *f = readdir(dir))
        {
            if (!f->d_name || f->d_name[0] == '.') 
            {
                continue;
            }
            if (f->d_type == DT_DIR)
            {
                listFilesRecusive(path + f->d_name + "/", cb);
            }
            if (f->d_type == DT_REG)
            {
                cb(path + f->d_name);
            }
        }
    }
    closedir(dir);
}

void listDirectorySelfDefined(const string &path) 
{
    DIR *baseDir = NULL, *subDir = NULL;
    string subDirPath = "";
    int subDirCnt = 0;
    
    if ((baseDir = opendir(path.c_str())) != NULL) 
    {
        while (struct dirent *f = readdir(baseDir))
        {
            if (!f->d_name || f->d_type == DT_REG || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR)
            {
                subDirPath = path + "/" + string(f->d_name);
                if ((subDir = opendir(subDirPath.c_str())) != NULL) 
                {
                    subDirCnt = 0;
                    while (struct dirent *g = readdir(subDir)) 
                    {
                        if (!g->d_name || g->d_type == DT_REG || g->d_name[0] == '.') continue;
                        if (g->d_type == DT_DIR) 
                        {
                            cout << string(f->d_name) + "/" + string(g->d_name) << endl;
                            subDirCnt++;
                        }
                    }
                    if (subDirCnt == 0) 
                    {
                        cout << string(f->d_name) << endl;
                    }
                }
                closedir(subDir);
            }
        }
    }
    closedir(baseDir);
}

void listDirectoryBoost(const string &path)
{
    string dir_path_name;
    int subdir_count = 0;
    directory_iterator end;

    for (directory_iterator ii(path); ii != end; ++ii)
    {
        dir_path_name = path + "/" + (*ii).path().filename().string();
        if (isDirectory(ii->path().string()))
        {
            subdir_count = 0;
            for (directory_iterator jj(dir_path_name); jj != end; ++jj) 
            {
                if (isDirectory(jj->path().string()))
                {
                    
                    cout << (*ii).path().filename().string() + "/" + 
                        (*jj).path().filename().string() << endl;
                    ++subdir_count;
                }
            }
            if (subdir_count == 0) 
            {
                cout << (*ii).path().filename().string() << endl;
            }
        }
    }
}

int main(int argc, char **argv)
{
    const string path = "/home/yunpengx/Projects/ottoware";
#if 0
    listFilesRecusive(path, [](const string &path) {
        cout << path << endl;
    });
#else
    cout << "self-defined: " << endl;
    listDirectorySelfDefined(path);

    cout << endl;

    cout << "boost: " << endl;
    listDirectoryBoost(path);
#endif
    return 0;
}
