#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <unistd.h>

const int INTMAX = 1000000007;

using namespace std;

void acceptConnections(int recfd, fd_set &master, int &fdmax, map<int, int> &IDs, set<string> &connects) {
    int neighfd;
    struct sockaddr_in neigh_addr;
    int nbytes;
    char buf[256];

    for (;;) {
        fd_set read_fds = master;
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == recfd) {
                    int sin_size = sizeof(struct sockaddr_in);
                    neighfd = accept(recfd, (struct sockaddr *)&neigh_addr, (socklen_t *)&sin_size);
                    if (neighfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(neighfd, &master);
                        fdmax = max(fdmax, neighfd);
                        recfds.push_back(neighfd);
                        nbytes = send(neighfd, ("&" + to_string(id)).c_str(), strlen(("&" + to_string(id)).c_str()), 0);
                        if (nbytes <= 0) {
                            if (nbytes == 0) {
                                FD_CLR(i, &master);
                                shutdown(neighfd, 2);
                            } else {
                                perror("send");
                            }
                        }
                    }
                } else {
                    nbytes = recv(i, buf, sizeof(buf), 0);
                    if (nbytes == 0) {
                        FD_CLR(i, &master);
                        shutdown(i, 2);
                    } else if (nbytes < 0) {
                        perror("recv");
                    } else {
                        string s = buf;
                        memset(buf, '\0', sizeof(char) * 256);
                        if (s[0] == '&') {
                            s.erase(0, 1);
                            int x = stoi(s);
                            IDs[i] = x;
                            cout << "Connected to " << nos_map[i] << " with unique-ID " << x << " on port " << port_map[i] << "\n";
                            connects.insert(s);
                            if (connects.size() >= nbrs) {
                                break;
                            }
                        } else {
                            s.erase(0, 1);
                            pendingmap[s] = i;
                        }
                    }
                }
            }
        }
        if (connects.size() >= nbrs)
            break;
    }
}

// Refactor other parts of the code in a similar manner

int main(int argc, char *argv[]) {

    // Main program logic
    acceptConnections(recfd, master, fdmax, IDs, connects);

    return 0;
}
