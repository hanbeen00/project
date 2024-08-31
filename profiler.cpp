#include "profiler.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <unistd.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Timer.h"
#include "Algorithm.h"
#include "CPU.h"
#include "Memory.h"

using namespace std;

int profiler::cnt_index() {
    index++;
    cout << index << endl;
    return index;
}

bool profiler::changedFlag() {
    return !flag;
}


// 현재 프로파일러의 시작 시간을 기록합니다.
void profiler::start_Time() {
    profiler::start_time =  chrono::high_resolution_clock::now();
}

// 현재 프로파일러의 종료 시간을 기록합니다.
void profiler::stop_Time() {
    profiler::stop_time =  chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = stop_time - start_time;
    cout << "Execution time: " << duration.count() << " ms" << endl;
}



void profiler::displayMenu(profiler * p) {
        int ch;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "              Client Manager                 " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. Display Client List                     " << endl;
        cout << "  2. Input Client                            " << endl;
        cout << "  3. Delete Client                           " << endl;
        cout << "  4. find index row                           " << endl;
        cout << "  5. Quit this Program                       " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << " What do you want to do? ";
        cin >> ch;
        cout << endl;

        if (ch == 5) {
            //break;
            _exit(0);
        }


        else if (ch == 2) {
            CPU c;
            Memory m;
            if (p->changedFlag()) {
                p->start_Time();
                c.start();
                m.printMemoryUsage();
            }


            algorithm();


            if (p->changedFlag()) {
                m.printMemoryUsage();
                delete[] large_array;
                p->stop_Time();
                c.end();
            }
        }

        cout << endl;
}
