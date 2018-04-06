#include <string>
#include <functional>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#ifdef PLATFORM_UBUNTU
#include "boost/filesystem.hpp"
#endif

using namespace std;
#ifdef PLATFORM_UBUNTU
using namespace boost::filesystem;
#endif

bool isDirectory(const string &path)
{
    struct stat buffer;
    return (!path.empty() &&
            stat(path.c_str(), &buffer) == 0 &&
            (buffer.st_mode & S_IFDIR));
}

#ifdef PLATFORM_UBUNTU
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
#endif

#if 0
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
#else
void listDirectorySelfDefined(const string &path) 
{
    DIR *baseDir = NULL, *subDir = NULL;
    string subDirPath = "";
    int subDirCnt = 0;

    if ((baseDir = opendir(path.c_str())) != NULL) 
    {
        while (struct dirent *f = readdir(baseDir))
        {
            string tmp1 = path + "/" + string(f->d_name);
            //cout << "f: " << tmp1 << endl;
            if (f->d_name[0] != '.' && isDirectory(tmp1)) 
            {
                subDirPath = tmp1;
                if ((subDir = opendir(subDirPath.c_str())) != NULL)
                {
                    subDirCnt = 0;
                    while (struct dirent *g = readdir(subDir))
                    {
                        string tmp2 = tmp1 + "/" + string(g->d_name);
                        //cout << "g: " << tmp2 << endl;
                        if (g->d_name[0] != '.' && isDirectory(tmp2))
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
#endif

#ifdef PLATFORM_UBUNTU
void listDirectoryOriginal(const string &path)
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
#endif

int main(int argc, char **argv)
{
#ifdef PLATFORM_UBUNTU
    const string path = "/home/yunpengx/Projects/ottoware";
#else
    const string path = "/";
#endif

#if 0
    listFilesRecusive(path, [](const string &path) {
            cout << path << endl;
            });
#endif

#ifdef PLATFORM_UBUNTU
    cout << "Original: " << endl;
    listDirectoryOriginal(path);
    cout << endl;
#endif

    cout << "self-defined: " << endl;
    listDirectorySelfDefined(path);
    return 0;
}
