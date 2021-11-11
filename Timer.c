#include "Timer.h"

void IRQ_HandleTimer()
{
    countedTime++;
    printf("%d", countedTime);
    PIC_sendEOI(0);
}