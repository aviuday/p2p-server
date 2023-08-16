#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <openssl/md5.h>

const int INTMAX = 1000000007;


int main(int argc, char *argv[]) {

    // Create and configure the listening socket
    int listeningSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Bind and listen
    if (bind(listeningSocket, (struct sockaddr *)&listeningAddr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(listeningSocket, 20)) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int sendfd[nbrs];

    // Accept incoming connections and exchange data
    for (;;) {
        read_fds = master;
        // ...

        // Handle new connection
        if (i == recfd) {
            neighfd = accept(recfd, (struct sockaddr *)&neigh_addr, (socklen_t *)&sin_size);
            if (neighfd == -1) {
                perror("accept");
            } else {
                //
            }
        } else {
            nbytes = recv(i, buf, sizeof(buf), 0);
            if (nbytes == 0) {
                // ...
            } else if (nbytes < 0) {
                perror("recv");
            } else {
                string s = buf;

                if (s[0] == '$') {
                    // 
                } else if (s[0] == '#') {
                    // 
                } else if (s[0] == '%') {
                    // 
                } else if (s[0] == '&') {
                    // 
                }
            }
        }
    }

    // Send and receive files
    for (;;) {
        read_fds = master;

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                nbytes = recv(i, buf, 1024, 0);
                if (nbytes == 0) {
                    // 
                } else if (nbytes < 0) {
                    perror("recv");
                } else {
                    string s = buf;
                    // 

                    if (s[0] == '$') {
                        // 
                    } else {
                        string name = *((port_files[i]).begin());
                        // 

                        // Write received data to file
                        int k = nbytes;
                        while (k > 0) {
                            // 
                        }
                        // 
                        bzero(buf, sizeof(buf));
                    }
                }
            }
        }
    }

    return 0;
}
