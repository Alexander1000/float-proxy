#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

// https://github.com/sameer2800/HTTP-PROXY/blob/master/proxy.cpp
// https://lecturesnet.readthedocs.io/net/low-level/ipc/socket/intro.html

int main(int argc, char** argv)
{
    int sockfd, newsockfd;

    struct sockaddr cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket

    if (sockfd < 0) {
        std::cout << "Err create socket" << std::endl;
        return 1;
    }

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6777);

    int binded = bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if (binded < 0) {
        std::cout << "Error on binding" << std::endl;
        return 1;
    }

    listen(sockfd, 100);

    int clilen = sizeof(struct sockaddr);

    while (1) {
        newsockfd = accept(sockfd, &cli_addr, (socklen_t*) &clilen);

        if (newsockfd < 0) {
            std::cout << "Error! On Accepting Request! i.e. requests limit crossed" << std::endl;
        }

        int pid = fork();
        if (pid == 0) {
            std::cout << "Data" << std::endl;
            close(newsockfd);
            break;
        } else {
            close(newsockfd);
            break;
        }
    }

    close(sockfd);

    return 0;
}
