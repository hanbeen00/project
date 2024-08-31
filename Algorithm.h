#define once
#include <stddef.h>

static char*large_array;

void algorithm(){
    // 측정할 알고리즘 작업////////////////

            // 메모리 할당
            size_t large_size = 100 * 1024 * 1024; // 약 100 MB
            large_array = new char[large_size];
            // 배열 초기화
            for (size_t i = 0; i < large_size; ++i) {
                large_array[i] = i;
            }
}