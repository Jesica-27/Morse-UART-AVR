#ifndef UTILS_H
#define UTILS_H

static void my_delay(unsigned int time)
{
    volatile unsigned int i, j;

    for(i=0; i<time; i++)
    {
        for(j=0; j<100; j++);
    }
}

#endif