#include "Memory.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

void Memory::printMemoryUsage() {
    ifstream statusFile("/proc/self/status");
    if (!statusFile.is_open()) {
        return;
    }

    string line;
    while (getline(statusFile, line)) {
        if (line.find("VmRSS") == 0) {
            VmRSS = line;
            cout << line << endl;
            break;
        }
    }
}