#include <stdio.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include "file.h"
#include "socket.h"
#include "shell.h"

void * clnt_handle(void * arg);

char s_path[1024];

int main(int argc, char * argv[]){
    int serv_sd, clnt_sd;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz=sizeof(clnt_adr);

    if(argc != 2){
        printf("Usage %s <port>\n", argv[0]);
        exit(1);
    }
    if(realpath(".", s_path) == NULL) {
        error_handling("realpath error");
    }
    printf("Running on %s\n", s_path);
    serv_sd = tcp_server_create(argv[1]);
    while(1){
        clnt_sd = accept(serv_sd, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
        if(clnt_sd == -1){
            error_handling("accept() error");
        }
        else{
            printf("Connected client %d\n", clnt_sd);
            pthread_t pid;
            pthread_create(&pid, 0x0, clnt_handle, &clnt_sd);
            pthread_detach(pid);
        }
    }
}

void * clnt_handle(void * arg){
    comm_st clnt_comm;
    int clnt_sd = *(int *)arg;
    char * path = strdup(s_path);
    res_st r_st;
    file * files;
    int fcount;
    file f_info;
    int exit = 0;
    while(1){
        read_full(clnt_sd, &clnt_comm, sizeof(comm_st));
        switch(clnt_comm.c){
            case CD:
                r_st.code = change_dir(&path, clnt_comm.arg);
                r_st.size = 0;
                write(clnt_sd, &r_st, sizeof(r_st));
                break;
            case LS:
                r_st.code = SUCCESS;
                fcount = get_files(path, &files);
                r_st.size = fcount * sizeof(file);
                if(fcount < 0){
                    r_st.size = 0;
                    r_st.code = UNDEFINED_ERR;
                }
                write(clnt_sd, &r_st, sizeof(r_st));
                write_v(clnt_sd, files, fcount, sizeof(file));
                free(files);
                break;
            case UP:
                read_full(clnt_sd, &f_info, sizeof(file));
                r_st.size = 0;
                r_st.code = SUCCESS;
                printf("UP %s(%lu)\n", f_info.name, f_info.size);
                if(read_to_file(clnt_sd, path, f_info) == -1){
                    r_st.code = UNDEFINED_ERR;
                }
                write(clnt_sd, &r_st, sizeof(r_st));
                break;
            case DL:
                get_file(".", &f_info, clnt_comm.arg);
                write(clnt_sd, &f_info, sizeof(file));
                write_from_file(clnt_sd, path, f_info);
                read_full(clnt_sd, &r_st, sizeof(r_st));
                break;
            case EXIT:
                exit = 1;
            default:
                break;
        }
        if(exit) break;
    }
    printf("disconnecting client %d\n", clnt_sd);
    close(clnt_sd);
    pthread_exit(0x0);
}
