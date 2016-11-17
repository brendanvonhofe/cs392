#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <netinet/in.h>
#include <netdb.h>
#include "my.h"
#include "list.h"

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    if(argc != 3) {
        my_str("Usage error, input host followed by port number.");
        exit(0);
    }

    int sockfd, portno;
    struct sockaddr_in *server;
    //struct hostent* host;
    struct pollfd polls[2];
    char username[32];
    char buffer[BUFSIZE];
    struct addrinfo** res = (struct addrinfo**)malloc(sizeof(struct addrinfo**));
    struct sockaddr* serv;
    socklen_t addrlen;

    my_str("Please input a username:");
    read(0, username, 32);
    for(int i = 0; i < 32; i++) {
        if(username[i] == '\n') {
            username[i] = 0;
        }
    }

    portno = my_atoi(argv[2]);
    //serv_size = (int)sizeof(server);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("Error opening client socket");
        exit(0);
    }

    if(getaddrinfo(argv[1], NULL, NULL, res) != 0) {
        perror("Error getting address info");
    }
    serv = (*res)->ai_addr;
    addrlen = (*res)->ai_addrlen;
    server = (struct sockaddr_in*)serv;
    server->sin_port = htons(portno);

    //host = gethostbyname(argv[1]);
/*
    if(host == NULL) {
        perror("Error, no such host");
        exit(0);
    }


    memset(&server, 0, serv_size);
    server.sin_family = AF_INET;
    memcpy(&server.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
    server.sin_port = htons(portno);
    */

    if(connect(sockfd, (struct sockaddr *)server, addrlen) < 0) {
        perror("Error connecting client to server");
        exit(0);
    }

    polls[0].fd = sockfd;
    polls[0].events = POLLIN;
    polls[1].fd = 0;
    polls[1].events = POLLIN;

    write(sockfd, username, 32);

    while(1) {
        poll(polls, 2, -1);
        if(polls[0].revents == POLLIN) {
            if(read(sockfd, buffer, BUFSIZE) < 0) {
                perror("Client error receiving data");
            }
            my_str(buffer);
            polls[0].revents = 0;
        }
        else if(polls[1].revents == POLLIN) {
            read(0, buffer, BUFSIZE);
            write(sockfd, buffer, BUFSIZE);

            if(buffer[0] == '/') {
                if(my_strncmp(buffer, "/exit", 5) == 0) {
                    exit(0);
                }
            }

            polls[0].revents = 0;
        }
        memset(buffer, 0, BUFSIZE);
    }

    close(sockfd);
    return 0;
}
