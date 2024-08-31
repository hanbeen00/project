#pragma once
#include <string>

using namespace std;


class Memory{
private:
    string VmRSS;

public:
    void printMemoryUsage();
};