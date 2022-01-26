#include "stdint.h"
#include "stdbool.h"
#include "HalTimer.h"
#include "stdlib.h"

void delay(uint32_t ms)
{
	uint32_t goal = Hal_timer_get_1ms_counter() + ms;

	while(goal != Hal_timer_get_1ms_counter());
}

void memclr(void* dst, uint32_t count)
{
    uint8_t* d = (uint8_t*)dst;

    for(uint32_t i = 0 ; i < count ; i++)
    {
	*d = 0;
	d++;
    }
}
