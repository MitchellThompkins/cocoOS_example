#include "pthread.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

#include "cocoos_public.h"

static pthread_t thread;
pthread_mutex_t timer_mutex;
pthread_mutex_t tick_mutex;

static bool timer_enable = false;
static bool timer_status;

static void lock_tick()
{
    pthread_mutex_lock(&tick_mutex);
}

static void unlock_tick()
{
    pthread_mutex_unlock(&tick_mutex);
}

//static void *tick(void *interval_ms)
static void *tick(void)
{
    static const uint16_t interval_us = 100*1000; // 0.1 seconds
    static volatile uint64_t global_time = 0;

    pthread_mutex_lock(&timer_mutex);
    timer_status = timer_enable;
    pthread_mutex_unlock(&timer_mutex);

    if(timer_status)
    {
        for(;;)
        {
            pthread_mutex_lock(&tick_mutex);
            os_tick();
            pthread_mutex_unlock(&tick_mutex);

            printf("global_time: %d\n", global_time);
            global_time++;
            usleep(interval_us);
        }
    }
}


void enable_timer(void)
{
    pthread_mutex_lock(&timer_mutex);
    timer_enable = true;
    pthread_mutex_unlock(&timer_mutex);
}

static void foo_task(void)
{
    task_open();

    for(;;)
    {
        printf("foo\n");
        task_wait( 10 );
    }

    task_close();
}

static void bar_task(void)
{
    task_open();

    for(;;)
    {
        uint16_t test = task_internal_state_get(running_tid);
        task_wait( 20 );
    }

    task_close();
}


int main(void)
{
    printf("hello world\n");

    int status = pthread_create(&thread, NULL, tick, NULL);
    enable_timer();

    os_init();

    const uint8_t f = task_create( foo_task, NULL, 2, NULL, 0, 0 );
    const uint8_t b = task_create( bar_task, NULL, 1, NULL, 0, 0 );

    os_start_locking(&lock_tick, &unlock_tick);

    // shouldn't hit this!
    printf("goodblye world\n");
}
