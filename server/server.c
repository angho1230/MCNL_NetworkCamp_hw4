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
#include "search.h"

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


    FILE * fp = fopen("search.data", "r");
    words_st words;
    read_data(&words, "search.data");
//    words_st * searchw = search_word(&words, "Pohang");
//    sort_word(searchw);
    
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
    int clnt_sd = *(int *)arg;

}
