#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

// https://github.com/sameer2800/HTTP-PROXY/blob/master/proxy.cpp
// https://lecturesnet.readthedocs.io/net/low-level/ipc/socket/intro.html

int main(int argc, char** argv)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket

    if (sockfd < 0) {
        std::cout << "Err create socket" << std::endl;
        return 1;
    }

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6777);

    bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    return 0;
}
