/*
*****************************************************************
*                          main函数
*****************************************************************
*/

#include "rtdef.h"
#include "rtthread.h"

struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

int main(void)
{
    /* 调度器初始化 */
    rt_system_scheduler_init();

    rt_thread_init( &rt_flag1_thread,
                    flag1_thread_entry,
                    RT_NULL,
                    &rt_flag1_thread_stack[0],
                    sizeof(rt_flag1_thread_stack) );
    rt_thread_insert_before( &(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist) );


    rt_thread_init( &rt_flag2_thread,
                    flag2_thread_entry,
                    RT_NULL,
                    &rt_flag2_thread_stack[0],
                    sizeof(rt_flag2_thread_stack) );
    rt_thread_insert_before( &(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist) );

    for (;;)
    {
    }
//  return 0;
}

void delay (rt_uint32_t count)
{
    for (; count != 0; count--);
}

//void thread1_entry(void)
//{
//  for(;;)
//  {
//    flag1 = 1;
//    delay(100);
//    flag1 = 0;
//    delay(100);
//  }
//}

//void thread2_entry(void)
//{
//  for(;;)
//  {
//    flag2 = 1;
//    delay(100);
//    flag2 = 0;
//    delay(100);
//  }
//}


