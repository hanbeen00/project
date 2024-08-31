#pragma once
#include <chrono>

using namespace std;

class Timer{
private:
    chrono::duration<double, milli> duration;
    chrono::high_resolution_clock::time_point start_time;
    chrono::high_resolution_clock::time_point stop_time;

public:
    void start_Time();
    void stop_Time();
};