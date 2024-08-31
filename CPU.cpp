#include "CPU.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>

using namespace std;


void* CPU::monitor_cpu_usage(void *arg) {
    CPU* cpu_instance = static_cast<CPU*>(arg); 
    FILE *pStat = NULL;
    char cpuID[6] = {0};

    stJiffies curJiffies = {};
    stJiffies prevJiffies = {};

    // 처음 prevJiffies를 초기화하기 위해 /proc/stat를 읽습니다.
    pStat = fopen("/proc/stat", "r");
    if (pStat != NULL) {
        fscanf(pStat, "%s %d %d %d %d", cpuID, &prevJiffies.user,
               &prevJiffies.nice, &prevJiffies.system, &prevJiffies.idle);
        fclose(pStat);
    }

    while (cpu_instance->running) {  // 스레드 실행 상태 확인
        pStat = fopen("/proc/stat", "r");
        if (pStat == NULL) {
            cerr << "Failed to open /proc/stat" << endl;
            usleep(300000); 
            continue;
        }

        fscanf(pStat, "%s %d %d %d %d", cpuID, &curJiffies.user,
               &curJiffies.nice, &curJiffies.system, &curJiffies.idle);

        stJiffies diffJiffies;
        diffJiffies.user = curJiffies.user - prevJiffies.user;
        diffJiffies.nice = curJiffies.nice - prevJiffies.nice;
        diffJiffies.system = curJiffies.system - prevJiffies.system;
        diffJiffies.idle = curJiffies.idle - prevJiffies.idle;

        int totalJiffies = diffJiffies.user + diffJiffies.nice + diffJiffies.system + diffJiffies.idle;

         if (totalJiffies > 0) {
            cpu_instance->cpu_usage = 100.0f * (1.0 - (diffJiffies.idle / (double) totalJiffies));
            if(cpu_instance->cpu_max < cpu_instance->cpu_usage){
                cpu_instance->cpu_max = cpu_instance->cpu_usage;
            }
        } else {
            cpu_instance->cpu_usage = 0.0f;  // default 값을 설정하거나 에러를 처리
        }

        //printf("Cpu usage : %.2f%%\n", cpu_instance->cpu_usage);

        prevJiffies = curJiffies;
        fclose(pStat);

        usleep(50000); // 루프 반복을 늦추기 위해 잠시 대기

        //printf("------------------------\n");
    }
    return NULL;
}

void CPU::start() { 
    running = true;  // 스레드가 실행 중임을 표시
    int res = pthread_create(&cpu_thread, NULL, monitor_cpu_usage, this);
    if (res != 0) {
        std::cerr << "Failed to create thread: " << res << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void CPU::end() {
    if (running) {
        running = false;  // 스레드 종료 신호를 보냄
        pthread_join(cpu_thread, NULL);  // 스레드가 종료될 때까지 대기
        printf("Cpu usage : %.2f%%\n", cpu_max);
        std::cout << "CPU monitoring thread has been terminated." << std::endl;
    }
}