#include <sys/socket.h>
#include <iostream>

int main(int argc, char** argv)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket

    if (sockfd < 0) {
        std::cout << "Err create socket" << std::endl;
        return 1;
    }

    struct sockaddr serv_addr;
    serv_addr.sa_family = AF_INET;

    bind(sockfd, &serv_addr, sizeof(serv_addr));

    return 0;
}
