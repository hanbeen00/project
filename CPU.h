#pragma once
#include <pthread.h>
#include <sys/types.h>

using namespace std;

class CPU{
private:
    float cpu_usage;
    float cpu_max=0;
    bool running; // 스레드 실행 상태를 나타내는 플래그

public:
    // CPU 사용량을 추적하는 기능
    pthread_t cpu_thread;
    struct stJiffies
    {
        int user;
        int nice;
        int system;
        int idle;
    };
    static void* monitor_cpu_usage(void *arg);
    void start();
    void end();
};
