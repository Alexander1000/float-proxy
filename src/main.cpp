#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

#include <float-proxy.h>

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

            int maxBufferSize = 4096;

            char buf[maxBufferSize];
            memset(buf, 0, maxBufferSize * sizeof(char));

            char* requestMessage = (char*) malloc(maxBufferSize);
            requestMessage[0] = '\0';

            int totalReceivBits = 0;

            while (strstr(requestMessage, "\r\n\r\n") == NULL) {
                std::cout << "Iter" << std::endl;

                int recvd = recv(newsockfd, buf, maxBufferSize, 0);
                if (recvd < 0) {
                    std::cout << "Error while receiving data" << std::endl;
                    return 2;
                } else if (recvd == 0) {
                    break;
                } else {
                    totalReceivBits += recvd;

                    buf[recvd] = '\0';
                    if (totalReceivBits > maxBufferSize) {
                        maxBufferSize *= 2;
                        requestMessage = (char*) realloc(requestMessage, maxBufferSize);
                    }
                }

                strcat(requestMessage, buf);
            }

            std::cout << requestMessage << std::endl;

            close(newsockfd);
            break;
        } else {
            close(newsockfd);
            std::cout << "Close" << std::endl;
            break;
        }
    }

    close(sockfd);

    return 0;
}
