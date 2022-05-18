#include "power.h"

int64_t power(int32_t n, int32_t p)
{
    int64_t result = n;
    
    if(p == 0)
    {
        return 1;
    }

    for(int64_t i = 1; i < p; i++)
    {
        result *= n;
    }
    	
    return result;
}

