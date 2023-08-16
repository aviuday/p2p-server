#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <dirent.h>
#include <bits/stdc++.h>
#include <chrono>

const int MAX_INT = 1000000007;

using namespace std;

static map<int, int> reverse_map(const map<int, int>& m) {
    map<int, int> reversed;
    for (const auto& kv : m)
        reversed[kv.second] = kv.first;
    return reversed;
}

int main(int argc, char* argv[]) {
    int serialNumber, myID, myPort, neighborCount;
    
    freopen(argv[2], "r", stdin);
    cin >> serialNumber >> myPort >> myID;
    cin >> neighborCount;

    int neighborIDs[neighborCount], neighborPorts[neighborCount];
    for (int i = 0; i < neighborCount; i++) {
        cin >> neighborIDs[i] >> neighborPorts[i];
    }

    int numFiles;
    cin >> numFiles;
    vector<string> fileNames;
    for (int i = 0; i < numFiles; i++) {
        string fileName;
        cin >> fileName;
        fileNames.push_back(fileName);
    }

    return 0;
}
