#pragma once
#include <chrono>
#include <string>
#include <atomic>
#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> //  setws
#include <pthread.h>
#include <unistd.h>


using namespace std;


class profiler {
protected:
    chrono::high_resolution_clock::time_point start_time;
    chrono::high_resolution_clock::time_point stop_time;

    string image_path;
    string model_name;
    double prediction;
    bool flag = false;



public:
    int index = -1;
    int cnt_index();
    bool changedFlag();
    void displayMenu(profiler*);


public:
     void start_Time();
     void stop_Time();

public:
    //static void printMemoryUsage();


public:

};


