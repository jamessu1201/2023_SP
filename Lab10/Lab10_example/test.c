#include "apue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void sig_handler();
int main(void)
{
    int i;
    signal(SIGALRM,sig_handler);
    alarm(5);
    for(i=1;i<7;i++){
        printf("sleep %d\n",i);
        sleep(1);
    }


    return 0;
}

void sig_handler()
{
    printf("catch the signal SIGINT\n");
}