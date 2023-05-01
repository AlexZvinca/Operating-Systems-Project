#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>

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
        printf("\u2022 n: name\n\u2022 d: size\n\u2022 a: access rights\n\u2022 c: total number of files with .c extension\n");
        return;
    }

    if(S_ISLNK(buf.st_mode)){
        printf("\u2022 n: name\n\u2022 l: delete symbolic link\n\u2022 d: size of symbolic link\n\u2022 t: size of target file\n\u2022 a: access rights\n");
        return;
    }
}

void input_options(char* path){

    struct stat buf;
    int check;


    check = lstat(path, &buf);
    if(check == -1){
        perror(strerror(errno));
        exit(errno);
    }


    printf("Please enter your options!\n");

    char s[10];
    int i, l;
    scanf("%s", s);

    if(s[0]!='-'){
        printf("Wrong input\n");
        exit(-1);
    }

    l = strlen(s);

    if(S_ISREG(buf.st_mode)){

        char filename[1024];

        for(i=1;i<l;i++){
            if(s[i]=='n'){
                
                int len = strlen(path);
                int count = 0, j = len;

                while(path[j]!='/' && j>=0){
                    j--;
                }

                while(j!=len){
                    filename[count++] = path[++j];
                }
                printf("The name is %s\n", filename);
            }

            if(s[i]=='d'){
                long size;
                size = buf.st_size;
                printf("The size is %ld bytes\n", size);
            }

            if(s[i]=='h'){
                int count;
                count = buf.st_nlink;
                printf("The number of hard links is %d\n", count);
            }

            if(s[i]=='m'){
                struct timespec ts;
                timespec_get(&ts, buf.st_mtime);
                printf("The last modification time is %ld.%.9ld\n", ts.tv_sec, ts.tv_nsec);
            }

            if(s[i]=='a'){
                printf("User:\n");
                    if(buf.st_mode & S_IRUSR){
                        printf("Read: YES\n");
                    }
                    else{
                        printf("Read: NO\n");
                    }

                    if(buf.st_mode & S_IWUSR){
                        printf("Write: YES\n");
                    }
                    else{
                        printf("Write: NO\n");
                    }

                    if(buf.st_mode & S_IXUSR){
                        printf("Exec: YES\n");
                    }
                    else{
                        printf("Exec: NO\n");
                    }

                printf("Group:\n");
                    if(buf.st_mode & S_IRGRP){
                        printf("Read: YES\n");
                    }
                    else{
                        printf("Read: NO\n");
                    }

                    if(buf.st_mode & S_IWGRP){
                        printf("Write: YES\n");
                    }
                    else{
                        printf("Write: NO\n");
                    }

                    if(buf.st_mode & S_IXGRP){
                        printf("Exec: YES\n");
                    }
                    else{
                        printf("Exec: NO\n");
                    }

                printf("Others:\n");
                    if(buf.st_mode & S_IROTH){
                        printf("Read: YES\n");
                    }
                    else{
                        printf("Read: NO\n");
                    }

                    if(buf.st_mode & S_IWOTH){
                        printf("Write: YES\n");
                    }
                    else{
                        printf("Write: NO\n");
                    }

                    if(buf.st_mode & S_IXOTH){
                        printf("Exec: YES\n");
                    }
                    else{
                        printf("Exec: NO\n");
                    }
                
            }

            if(s[i]=='l'){
                char link_name[1024];

                printf("Input name of link: ");
                scanf("%s", link_name);

                check = symlink(path, link_name);
                if(check == -1){
                    perror(strerror(errno));
                    exit(errno);
                }

                printf("Link has been created!\n");
            }
        }

        return;
    }
            
        

    if(S_ISDIR(buf.st_mode)){

        for(i=1;i<l;i++){
            switch(s[i]){
                case 'n':{
                    char filename[1024];
                    int len = strlen(path);
                    int count = 0, j = len;

                    while(path[j]!='/' && j>=0){
                        j--;
                    }

                    while(j!=len){
                        filename[count++] = path[++j];
                    }

                    printf("The name is %s\n", filename);

                    break;
                }

                case 'd':{
                    long size;
                    size = buf.st_size;
                    printf("The size is %ld bytes\n", size);
                    break;
                }

                case 'a':
                    printf("User:\n");
                        if(buf.st_mode & S_IRUSR){
                            printf("Read: YES\n");
                        }
                        else{
                            printf("Read: NO\n");
                        }

                        if(buf.st_mode & S_IWUSR){
                            printf("Write: YES\n");
                        }
                        else{
                            printf("Write: NO\n");
                        }

                        if(buf.st_mode & S_IXUSR){
                            printf("Exec: YES\n");
                        }
                        else{
                            printf("Exec: NO\n");
                        }

                    printf("Group:\n");
                        if(buf.st_mode & S_IRGRP){
                            printf("Read: YES\n");
                        }
                        else{
                            printf("Read: NO\n");
                        }

                        if(buf.st_mode & S_IWGRP){
                            printf("Write: YES\n");
                        }
                        else{
                            printf("Write: NO\n");
                        }

                        if(buf.st_mode & S_IXGRP){
                            printf("Exec: YES\n");
                        }
                        else{
                            printf("Exec: NO\n");
                        }

                    printf("Others:\n");
                        if(buf.st_mode & S_IROTH){
                            printf("Read: YES\n");
                        }
                        else{
                            printf("Read: NO\n");
                        }

                        if(buf.st_mode & S_IWOTH){
                            printf("Write: YES\n");
                        }
                        else{
                            printf("Write: NO\n");
                        }

                        if(buf.st_mode & S_IXOTH){
                            printf("Exec: YES\n");
                        }
                        else{
                            printf("Exec: NO\n");
                        }
                    break;
                    
                case 'c':{
                    DIR *dir;
                    dir = opendir(path);

                    if(dir == NULL){
                        perror(strerror(errno));
                        exit(errno);
                    }

                    struct dirent *entry;
                    int counter = 0;

                    entry = readdir(dir);
                    while(entry!=NULL){
                        
                        //printf("%s %c %c\n", entry->d_name, entry->d_name[strlen(entry->d_name)-1], entry->d_name[strlen(entry->d_name)-1]);
                        if(entry->d_name[strlen(entry->d_name)-1]=='c' && entry->d_name[strlen(entry->d_name)-2]=='.'){
                            counter++;
                        }

                        entry = readdir(dir);
                        
                    }

                    check = closedir(dir);
                    if(check == -1){
                        perror(strerror(errno));
                        exit(errno);
                    }

                    printf("There are %d files with the .c extension in this directory.\n", counter);
                    break;
                }
            }
        }
        return;
    }

    if(S_ISLNK(buf.st_mode)){
        for(i=1;i<l;i++){
            if(s[i]=='n'){

                char filename[1024];
                int len = strlen(path);
                int count = 0, j = len;

                while(path[j]!='/' && j>=0){
                    j--;
                }

                while(j!=len){
                filename[count++] = path[++j];
                }
                
                printf("The name is %s\n", filename);

            }

            if(s[i]=='l'){
                check = unlink(path);

                if(check == -1){
                    perror(strerror(errno));
                    exit(errno);
                }

                printf("Symbolic link has been deleted\n");
                return;
            }

            if(s[i]=='d'){
                long size;
                size = buf.st_size;
                printf("The size is %ld bytes\n", size);
            }

            if(s[i]=='t'){
                struct stat buf2;

                check = stat(path, &buf2);
                if(check == -1){
                    perror(strerror(errno));
                    exit(errno);
                }

                long size;
                size = buf2.st_size;
                printf("The size is %ld bytes\n", size);
            }

            if(s[i]=='a'){
                printf("User:\n");
                    if(buf.st_mode & S_IRUSR){
                        printf("Read: YES\n");
                    }
                    else{
                        printf("Read: NO\n");
                    }

                    if(buf.st_mode & S_IWUSR){
                        printf("Write: YES\n");
                    }
                    else{
                        printf("Write: NO\n");
                    }

                    if(buf.st_mode & S_IXUSR){
                        printf("Exec: YES\n");
                    }
                    else{
                        printf("Exec: NO\n");
                    }

                printf("Group:\n");
                    if(buf.st_mode & S_IRGRP){
                        printf("Read: YES\n");
                    }
                    else{
                        printf("Read: NO\n");
                    }

                    if(buf.st_mode & S_IWGRP){
                        printf("Write: YES\n");
                    }
                    else{
                        printf("Write: NO\n");
                    }

                    if(buf.st_mode & S_IXGRP){
                        printf("Exec: YES\n");
                    }
                    else{
                        printf("Exec: NO\n");
                    }

                printf("Others:\n");
                    if(buf.st_mode & S_IROTH){
                        printf("Read: YES\n");
                    }
                    else{
                        printf("Read: NO\n");
                    }

                    if(buf.st_mode & S_IWOTH){
                        printf("Write: YES\n");
                    }
                    else{
                        printf("Write: NO\n");
                    }

                    if(buf.st_mode & S_IXOTH){
                        printf("Exec: YES\n");
                    }
                    else{
                        printf("Exec: NO\n");
                    }
            }
        }
        return;
    }
    
}

int main(int argc, char* argv[]){
    

    if(argc == 1){
        printf("Not enough arguments\n");
        exit(-1);
    }

    for(int i=1;i<argc;i++){
    
        //get path
        char path[1024];
        strcpy(path, argv[i]);
        

        //get filename
        char filename[1024];
        int len = strlen(path);
        int count = 0, j = len;

        while(path[j]!='/' && j>=0){
            j--;
        }

        while(j!=len){
            filename[count++] = path[++j];
        }
    
        printf("%s - ", filename);
        
        //use lstat on file and print file type
        int check;
        struct stat buf;
        
        check = lstat(path, &buf);
        if(check == -1){
            perror(strerror(errno));
            exit(errno);
        }

        print_type(buf);

        //print Menu for file type
        menu(buf);

        //input of the desired options
        input_options(path);
    }

    return 0;
}
