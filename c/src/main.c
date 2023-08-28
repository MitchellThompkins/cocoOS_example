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

static void *tick(void* interval_ms)
{
    const uint32_t interval_us = (*((int*)interval_ms))*1000; // 0.1 seconds

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
        printf("after foo\n");
    }

    task_close();
}

static void bar_task(void)
{
    // if for is specified below, we should start here
    task_open();

    for(;;)
    {
        // we should reenter here
        printf("bar\n");
        task_wait( 20 );

        // Need to "resume" operation here
        printf("after bar\n");
    }

    // if for is specified above, we should never call this
    task_close();
}

static void foobar_task(void)
{
    task_open();

    printf("foobar\n");
    task_wait( 5 );
    printf("after foobar\n");

    task_close();
}


int main(void)
{
    printf("hello world\n");

    uint32_t interval_ms = 100;
    int status = pthread_create(&thread, NULL, (void*)tick, &interval_ms);
    enable_timer();

    os_init();

    const uint8_t f = task_create( foo_task, NULL, 2, NULL, 0, 0 );
    const uint8_t b = task_create( bar_task, NULL, 1, NULL, 0, 0 );
    const uint8_t fb = task_create( foobar_task, NULL, 3, NULL, 0, 0 );

    os_start_locking(&lock_tick, &unlock_tick);

    // shouldn't hit this!
    printf("goodblye world\n");
}
