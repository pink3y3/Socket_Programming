//helper functions

//include guards - header file is icnluded only once when project is compiled
#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>  //convert IP address inet_pton()
#include <sys/socket.h>  //core socket functions - socket(),bind()
#include <netinet/in.h> //definitions for internet addresses

#define PORT 10200 //server listens on and client connects to
#define IP "127.0.0.1"  //IP of server(here,my computer)

int makeIP4Socket(){
    return socket(AF_INET,SOCK_STREAM,0); //IPv4 address fam,TCP connection(beej's),default protocol like TCP for SOCK_STREAM AND UDP for SOCK_DGRAM
}

struct sockaddr_in assignSocketAddress(){
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;  //addr family, must be af_inet for ipv4
    addr.sin_port=htons(PORT); //port number hbo to network short big endian(beej)
    inet_pton(AF_INET,IP,&addr.sin_addr.s_addr); // ip address inet_pton -> human readable to binary
    return addr;
}

#endif //closes include guard at the top