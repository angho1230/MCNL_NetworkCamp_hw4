#include <stdio.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include "socket.h"
#include "search.h"

void * clnt_handle(void * arg);

words_st words;

int main(int argc, char * argv[]){
    int serv_sd, clnt_sd;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz=sizeof(clnt_adr);

    if(argc != 2){
        printf("Usage %s <port>\n", argv[0]);
        exit(1);
    }


    FILE * fp = fopen("search.data", "r");
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
    char buf[1024];
    while(1){
        int r = read(clnt_sd, buf, 1024);
        if(r == 0){
            printf("Disconnected client %d\n", clnt_sd);
            break;
        }
        buf[r-1] = '\0';
        printf("%d : %s\n", clnt_sd, buf);
        words_st * searchw = search_word(&words, buf);
        sort_word(searchw);
        char ** strs = trie_to_str(searchw);
        int len = searchw->size >= 10 ? 10 : searchw->size; 
        write(clnt_sd, &len, sizeof(int));
        for(int i = 0; i < len; i++){
            int strl = strlen(strs[i]);
            write(clnt_sd, &strl, sizeof(int));
            write(clnt_sd, strs[i], strlen(strs[i]));
        }
    }
    close(clnt_sd);
    return 0x0;
}
