#include <iostream>
#include <unistd.h>  //read

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   //open
#include <cstring>

#define MAX_LINE_LEN 1000

#define OPEN_ERROR(x) ((x)==-1)


int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    char *file_path_from;
    char *file_path_to;

    char buf[MAX_LINE_LEN + 1];

    int fd_from;
    int fd_to;
    int flag;

    int select;

    if (argc != 3 || !argv[1] || !argv[2]) {
        fprintf(stderr, "Usage: %s <source file path> <target file path>\n", argv[0]);
        exit(-1);
    }
    file_path_from = argv[1];
    file_path_to = argv[2];

    fd_from = open(file_path_from, O_RDONLY);
    if (OPEN_ERROR(fd_from)) {
        fprintf(stderr, "open %s happen error:\n", argv[1]);
//        perror("open");
        fprintf(stderr, "\t %s with %d\n", strerror(errno), errno);
        exit(-1);
    }

    if (!access(file_path_to, F_OK)) {     //文件存在
        printf("file is exist\n");
        printf("１.取消操作\n2.强制删除并复制\n");
        scanf("%d", &select);
        while (select != 1 && select != 2) {
            printf("１.取消操作\n2.清空文件并复制\n");
            scanf("%d", &select);
        }
        switch (select) {
            case 1:
                return 0;

            case 2:
                fd_to = open(file_path_to, O_TRUNC);//若文件存在并且以可写的方式打开时, 此旗标会令文件长度清为0, 而原来存于该文件的资料也会消失.
                if (OPEN_ERROR(fd_to)) {
                    fprintf(stderr, "create %s happen error\n", argv[2]);
                    fprintf(stderr, "\t %s with %d\n", strerror(errno), errno);
                    exit(-1);
                }
                break;
            default:
                break;
        }
    } else {
        fd_to = open(file_path_to, O_WRONLY | O_CREAT);         //新建文件
        if (OPEN_ERROR(fd_to)) {
            fprintf(stderr, "create %s happen error\n", argv[2]);
//            perror("create");
            fprintf(stderr, "\t %s with %d\n", strerror(errno), errno);
            exit(-1);
        }
    }
    while ((flag = read(fd_from, buf, MAX_LINE_LEN)) > 0) {
        write(fd_to, buf, flag);
    }
    close(fd_from);
    close(fd_to);


    return 0;
}