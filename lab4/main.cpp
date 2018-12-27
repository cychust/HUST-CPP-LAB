#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#include <pwd.h>
#include <grp.h>
#include <cstring>


void displayFile(char *pathName) {
    struct stat buf;
    struct tm *time;
    char filemode[10];
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
    std::cout << filemode << "  ";
    std::cout << buf.st_nlink << "  ";
    std::cout << getpwuid(buf.st_uid)->pw_name << "  ";
    std::cout << buf.st_size << "   ";
    std::cout << getgrgid(buf.st_gid)->gr_name << "  ";
    std::cout << time->tm_year + 1900 << "-" << time->tm_mon + 1 << "-" << time->tm_mday << "  ";
    std::cout << time->tm_hour << ":" << time->tm_min << "  ";
    std::cout << pathName << std::endl;
}

void displayDir(char *dirName) {
    DIR *dir;
    struct dirent *direntp;
    struct stat buf;
    dir = opendir(dirName);
    if (dir == NULL) {
        perror("error");
        return;

    }
//    chdir(dirName);
    while ((direntp = readdir(dir)) != NULL) {
//        std::cout << direntp->d_name << " ";
        if (lstat(direntp->d_name, &buf) < 0) {
            perror("sss");
        }
        if (S_ISDIR(buf.st_mode)) {
            if (strcmp(direntp->d_name, "..") == 0 || strcmp(direntp->d_name, ".") == 0)
                continue;
            displayFile(direntp->d_name);
//            displayDir(direntp->d_name);
        }
        else
            displayFile(direntp->d_name);
    }

//    chdir("..");
    closedir(dir);
}

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
//    FLAGS_logtostderr = 1;
//    google::InitGoogleLogging(argv[0]);

    struct stat buf;
    char *ptr;
    for (int i = 1; i < argc; ++i) {
        if (lstat(argv[i], &buf) < 0) {
            perror("lstat error");
            continue;
        }
        if (S_ISDIR(buf.st_mode)) {
            ptr = "dir";
            displayDir(argv[i]);
        } else {
            displayFile(argv[i]);
        }
        std::cout << ptr << std::endl;
    }
    return 0;
}