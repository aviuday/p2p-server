#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <dirent.h>
using namespace std;

int main(int argc, char *argv[]) {
    int sno, id, myport, nbrs;

    // Simulate reading from configuration data
    sno = 123; // Example serial number
    myport = 5000; // Example port number
    id = 42; // Example unique ID
    nbrs = 2; // Example number of neighbors

    int nos[nbrs], ports[nbrs];
    for (int i = 0; i < nbrs; i++) {
        nos[i] = i + 1; // Example neighboring server ID
        ports[i] = 6000 + i; // Example neighboring server port
    }

    // Simulate reading directory
    cout << "Files in directory " << argv[1] << ":" << endl;
    cout << "file1.txt" << endl;
    cout << "file2.txt" << endl;

    int recfd, neighfd;
    struct sockaddr_in rec_addr, neigh_addr;
    recfd = socket(AF_INET, SOCK_STREAM, 0);

    // Simulate binding
    cout << "Binding to port " << myport << "..." << endl;

    // Simulate listening
    cout << "Listening on port " << myport << "..." << endl;

    int sendfd[nbrs];
    fd_set master, read_fds;
    int fdmax, nbytes;

    char buf[256];
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    // Simulate adding server socket to master set
    FD_SET(recfd, &master);
    fdmax = recfd;

    // Simulate connecting to neighboring servers
    for (int i = 0; i < nbrs; i++) {
        sendfd[i] = socket(AF_INET, SOCK_STREAM, 0);

        // Simulate connecting
        cout << "Connecting to neighboring server " << nos[i] << " on port " << ports[i] << "..." << endl;

        FD_SET(sendfd[i], &master);
        fdmax = max(fdmax, sendfd[i]);
    }

    for (;;) {
        read_fds = master;

        // Simulate select
        cout << "Waiting for incoming data..." << endl;

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == recfd) {
                    neighfd = accept(recfd, (struct sockaddr *)&neigh_addr, NULL);
                    if (neighfd == -1) {
                        perror("accept");
                    } else {
                        // Simulate sending unique ID
                        string uniqueId = to_string(id);
                        nbytes = send(neighfd, uniqueId.c_str(), uniqueId.size(), 0);
                        if (nbytes <= 0) {
                            if (nbytes == 0) {
                                FD_CLR(i, &master);
                                cout << "selectserver: socket " << i << " hung up" << endl;
                                shutdown(neighfd, 2);
                            } else {
                                perror("send");
                            }
                        } else {
                            // cout << nbytes << endl;
                        }
                    }
                } else {
                    // Simulate receiving data
                    string receivedData = "42";
                    nbytes = receivedData.size();
                    if (nbytes == 0) {
                        FD_CLR(i, &master);
                        cout << "selectserver: socket " << i << " hung up" << endl;
                        shutdown(i, 2);
                    } else if (nbytes < 0) {
                        perror("recv");
                    } else {
                        int x = atoi(receivedData.c_str());
                        cout << "Connected with unique-ID " << x << endl;
                    }
                }
            }
        }
    }
    return 0;
}
