#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

void print_type(struct stat buf){

    //check POSIX flags
    if(S_ISREG(buf.st_mode)){
        printf("REGULAR\n");
    }

    if(S_ISDIR(buf.st_mode)){
        printf("DIRECTORY\n");
    }

    if(S_ISLNK((buf.st_mode))){
        printf("SYMBOLIC LINK\n");
    }

    /*if(S_ISCHAR((buf.st_mode))){
        strcpy(type, "CHARACTER DEVICE");
        return type;
    }

    if(S_ISBLK((buf.st_mode))){
        strcpy(type, "BLOCK DEVICE");
        return type;
    }

    if(S_ISFIFO((buf.st_mode))){
        strcpy(type, "FIFO");
        return type;
    }*/
}

int main(int argc, char* argv[]){
    
    //verify if the argument number is wrong
    if(argc != 3){
        printf("Wrong number of arguments");
        exit(-1);
    }

    //get and print name of file
    char filename[1024];
    strcpy(filename, argv[1]);
    printf("%s - ", filename);
    
    //use lstat on file and print file type
    int check;
    struct stat buf;
    check = lstat(filename, &buf);
    if(check == -1){
        perror(strerror(errno));
        exit(errno);
    }

    print_type(buf);
    return 0;
}