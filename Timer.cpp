#include "Timer.h"
#include <iostream>

using namespace std;


// 현재 프로파일러의 시작 시간을 기록합니다.
void Timer::start_Time() {
    Timer::start_time =  chrono::high_resolution_clock::now();
}


// 현재 프로파일러의 종료 시간을 기록합니다.
void Timer::stop_Time() {
    Timer::stop_time =  chrono::high_resolution_clock::now();
    duration = stop_time - start_time;
    cout << "Execution time: " << duration.count() << " ms" << endl;
}