#include <iostream>
#include "profiler.h"  
#include <stddef.h>

int main(void)
{
    profiler p;

    while(1){
        p.displayMenu(&p);
    }

    return 0;
}