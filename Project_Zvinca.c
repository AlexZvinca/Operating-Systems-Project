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

void menu(struct stat buf){
    printf("---- MENU ----\n");

    if(S_ISREG(buf.st_mode)){
        printf("\u2022 n: name\n\u2022 d: size\n\u2022 h: hard link count\n\u2022 m: time of last modification\n\u2022 a: access rights\n\u2022 l: create symbolic link\n");
        return;
    }

    if(S_ISDIR(buf.st_mode)){
        printf("Will be added\n");
        return;
    }

    if(S_ISLNK(buf.st_mode)){
        printf("\u2022 n: name\n\u2022 l: delete symbolic link\n\u2022 d: size of symbolic link\n\u2022 t: size of target file\n\u2022 a: access rights\n");
        return;
    }
}

int main(int argc, char* argv[]){
    
    //verify if the argument number is wrong
    /*if(argc != 3){
        printf("Wrong number of arguments");
        exit(-1);
    }*/

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

    //print Menu for file type
    menu(buf);

    return 0;
}