#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#include <pwd.h>
#include <grp.h>
#include <cstring>
#include <zconf.h>
#include <list>
#include <string>
#include <iomanip>
//--------------------------------------------------------------------------------
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

//---------------------------------------------------------------------------------

void displayFile(char *pathName) {
    struct stat buf;
    struct tm *time;
    char filemode[11];
    char symlink[100];
    if (lstat(pathName, &buf) < 0) {
        perror("lstat error");
        return;
    }
    switch (buf.st_mode & S_IFMT) {
        case S_IFREG:
            filemode[0] = '-';
            break;
        case S_IFSOCK:
            filemode[0] = 's';
            break;
        case S_IFLNK:
            filemode[0] = 'l';
            break;
        case S_IFBLK:
            filemode[0] = 'b';
            break;
        case S_IFDIR:
            filemode[0] = 'd';
            break;
        case S_IFCHR:
            filemode[0] = 'c';
            break;
        case S_IFIFO:
            filemode[0] = 'p';
            break;
        default:
            perror("none type");
            break;
    }
    int i = 0;
    while (i < 9) {
        if (buf.st_mode & (1 << i)) {
            switch (i % 3) {
                case 0:
                    filemode[9 - i] = 'x';
                    break;
                case 1:
                    filemode[9 - i] = 'w';
                    break;
                case 2:
                    filemode[9 - i] = 'r';
                    break;
            }
        } else {
            filemode[9 - i] = '-';
        }
        i++;
    }
    time = localtime(&buf.st_mtime);
    filemode[10] = '\0';
    std::cout << filemode << "  ";
    std::cout << buf.st_nlink << "  ";
    std::cout << std::setw(4) << std::setfill(' ') << getpwuid(buf.st_uid)->pw_name << "  ";
    std::cout << std::setw(4) << getgrgid(buf.st_gid)->gr_name << "  ";
    if (filemode[0] == 'b' || filemode[0] == 'c')
        std::cout << (buf.st_rdev >> 8) << " " << (buf.st_rdev & 0xff);
    else
        std::cout << std::setw(7) << std::right << buf.st_size << "   ";
    std::cout << time->tm_year + 1900 << "-" << time->tm_mon + 1 << "-" << time->tm_mday << "  ";   //时间

    std::cout << std::setw(2) << std::setfill('0') << time->tm_hour             //时间
              << ":"
              << std::setw(2) << time->tm_min << "  ";
    if (filemode[0] == 'l') {
        memset(symlink, '\0', sizeof(symlink));
        std::cout << pathName;
        if (readlink(pathName, symlink, sizeof(symlink)) > 0) {
            symlink[strlen(symlink)] = '\0';
            std::cout << " -> " << symlink;
        }
    } else {
        std::cout << pathName;
    }
    std::cout << std::endl;
//    else
//        std::cout<<
}

void displayDir(char *fileName, const char *dirName) {
    std::list<dirent *> direntpList;
    DIR *dir;
    struct dirent *direntp;
    struct stat buf;
    std::cout << dirName << ":" << std::endl;
    dir = opendir(fileName);
    if (dir == NULL) {
        perror("error");
        return;
    }
    chdir(fileName);
    while ((direntp = readdir(dir)) != NULL) {
        if (lstat(direntp->d_name, &buf) < 0) {
            perror("sss");
        }
        if (S_ISDIR(buf.st_mode)) {
            if (strcmp(direntp->d_name, "..") == 0 || strcmp(direntp->d_name, ".") == 0)
                continue;
            displayFile(direntp->d_name);
            direntpList.push_back(direntp);
        } else
            displayFile(direntp->d_name);
    }
    std::cout << std::endl;
    for (std::list<dirent *>::iterator itr = direntpList.begin(); itr != direntpList.end(); itr++) {
        std::string dirN = std::string(dirName) + "/" + (*itr)->d_name;
        displayDir((*itr)->d_name, dirN.data());
        std::cout << std::endl;
    }
    chdir("..");
    closedir(dir);
}

int main(int argc, char *argv[]) {
    struct stat buf;
    for (int i = 1; i < argc; ++i) {
        if (lstat(argv[i], &buf) < 0) {
            perror("lstat error");
            continue;
        }
        if (S_ISDIR(buf.st_mode)) {
            displayDir(argv[i], argv[i]);
        } else {
            displayFile(argv[i]);
        }
    }
    return 0;
}