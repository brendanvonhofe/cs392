#include <stdio.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include "my.h"
#include "list.h"

#define BUFSIZE 1024


char *get_nick(char *buffer) {
    char *output = (char*)malloc(sizeof(char)*1024);

    int i;
    for(i = 0; i <= BUFSIZE; i++) {
        if(buffer[i] == ' ') {
            i++;
            break;
        }
    }
    int j = 0;
    while(buffer[i] != '\0') {
        if(buffer[i] == '\n') output[j] = 0;
        output[j] = buffer[i];
        i++; j++;
    }
    return output;
}

void fix_me(char *buffer) {
    for(int i = 0; i < 1021; i++) {
        buffer[i] = buffer[i+4];
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        my_str("Usage error: enter only the port number.\n");
        exit(0);
    }

    struct user {
        int sockfd;
        char *username;
    };

    struct s_node* node = NULL;
    struct s_node** head = &node;

    int sockfd, portno;
    char buffer[1024];
    char buf2[1024];
    char username[32];
    struct sockaddr_in server;
    socklen_t serv_size = sizeof(server);
    nfds_t nfds = 1;
    int special = 0;


    memset(buffer, 0, BUFSIZE);
    memset(buf2, 0, BUFSIZE);
    memset(username, 0, 32);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("Error opening server socket.");
        exit(0);
    }

    portno = my_atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &server, serv_size) < 0) {
        perror("Error binding server");
        exit(0);
    }

    listen(sockfd, 5);

    while(1) {
        int cli_sockfd;
        struct pollfd polls[nfds];

        polls[0].fd = sockfd;
        polls[0].events = POLLIN;

        for(int i = 0; i < count_s_nodes(*head); i++) {
            if(elem_at(*head, i) == NULL) {
                continue;
            }
            polls[i+1].fd = ((struct user*)(elem_at(*head, i)))->sockfd;
            polls[i+1].events = POLLIN;
        }

        poll(polls, nfds, -1);

        if(polls[0].revents == POLLIN) {
            cli_sockfd = accept(sockfd, (struct sockaddr *) &server, &serv_size);
            nfds++;
            struct user *newuser = (struct user*)malloc(sizeof(struct user));
            newuser->username = (char*)malloc(sizeof(char)*32);
            read(cli_sockfd, username, 32);
            newuser->sockfd = cli_sockfd;
            newuser->username = my_strdup(username);
            struct s_node* node = new_node(newuser, NULL, NULL);
            append(node, head);
            polls[0].revents = 0;
            memset(username, 0, 32);
        }
        else {
            int messagefd = 0;
            int node_num;
            for(int i = 1; i < nfds; i++) {
                if(polls[i].revents == POLLIN) {
                    messagefd = polls[i].fd;
                    node_num = i-1;
                    my_strcat(buf2, ((struct user*)(elem_at(*head, node_num)))->username);
                    my_strcat(buf2, ": ");
                    break;
                }
                else if(polls[i].revents == POLLPRI) {
                    my_str("pollpri");
                }
                else if(polls[i].revents == POLLOUT) {
                    my_str("pollout");
                }
                else if(polls[i].revents == POLLERR) {
                    my_str("pollerr");
                }
                else if(polls[i].revents == POLLHUP) {
                    my_str("pollhup");
                }
                else if(polls[i].revents == POLLNVAL) {
                    my_str("pollnval");
                }
            }
            if(read(messagefd, buffer, BUFSIZE) < 0) {
                perror("Error receiving data");
                exit(0);
            }

            //my_str(buffer);

            if(buffer[0] == '/') {
                if(my_strncmp(buffer, "/exit", 5) == 0) {
                    if(nfds == 2) {
                        head = &node;
                        nfds--;
                        special = 1;
                    }
                    else {
                        remove_node_at(head, node_num);
                        nfds--;
                        special = 1;
                    }
                }
                else if(my_strncmp(buffer, "/nick", 5) == 0) {
                    char *new_name = get_nick(buffer);
                    int i;
                    for(i = 0; new_name[i] != '\n'; i++) {}
                    new_name[i] = 0;
                    ((struct user*)(elem_at(*head, node_num)))->username = new_name;
                    memset(buf2, 0, BUFSIZE);
                    my_strcat(buf2, new_name);
                    my_strcat(buf2, ": ");
                    special = 1;
                }
                else if(my_strncmp(buffer, "/me", 3) == 0) {
                    char *mess = get_nick(buffer);
                    my_str(mess);
                    memset(buf2, 0, BUFSIZE);
                    my_strcat(buf2, ((struct user*)(elem_at(*head, node_num)))->username);
                    my_strcat(buf2, " ");
                    my_strcat(buf2, mess);
                    for(int j = 0; j < nfds-1; j++) {
                        write(((struct user*)(elem_at(*head, j)))->sockfd, buf2, BUFSIZE);
                    }
                    special = 1;
                }
            }

            if(special == 0) {
                my_strcat(buf2, buffer);
                for(int j = 0; j < nfds-1; j++) {
                    write(((struct user*)(elem_at(*head, j)))->sockfd, buf2, BUFSIZE);
                }
            }
            polls[messagefd].revents = 0;
            memset(buffer, 0, BUFSIZE);
            memset(buf2, 0, BUFSIZE);
            special = 0;
        }
    }

    close(sockfd);
}
