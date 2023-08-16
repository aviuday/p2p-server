#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <arpa/inet.h>

const int INTMAX = 1000000007;

// Function to send data to a socket
int sendData(int sockfd, const std::string &data) {
    return send(sockfd, data.c_str(), data.size(), 0);
}

int main(int argc, char *argv[]) {

    // Create a listening socket
    int listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listeningSocket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int yes = 1;
    if (setsockopt(listeningSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Bind and listen
    struct sockaddr_in listeningAddr;
    listeningAddr.sin_family = AF_INET;
    listeningAddr.sin_port = htons(myport);
    listeningAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(listeningAddr.sin_zero), '\0', 8);

    if (bind(listeningSocket, (struct sockaddr *)&listeningAddr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(listeningSocket, 20)) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Clean up and close sockets
    close(listeningSocket);

    return 0;
}
