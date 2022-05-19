#include "power.h"

int64_t power(int32_t n, int32_t p)
{
    int64_t result = 1;

    for(int64_t i = 0; i < p; i++)
        result *= n;
    	
    return result;
}

