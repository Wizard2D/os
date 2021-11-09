#include "Timer.h"

countedTime = 0;

void IRQ_HandleTimer()
{
    countedTime++;
    printf("%d", countedTime);
    PIC_sendEOI(0);
}