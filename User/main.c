/*
*****************************************************************
*                          main����
*****************************************************************
*/

/*
*****************************************************************
*                           ������ͷ�ļ�
*****************************************************************
*/

#include "rtthread.h"
#include "ARMCM3.h"
#include <rthw.h>
/*
*****************************************************************
*                           ȫ�ֱ���
*****************************************************************
*/
rt_uint8_t flag1;
rt_uint8_t flag2;

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];


/*
*****************************************************************
*                    �߳̿��ƿ�&STACK&�߳�����
*****************************************************************
*/
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

ALIGN(RT_ALIGN_SIZE)
/* �����߳�ջ */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];

/* �߳����� */
void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);

/*
*****************************************************************
*                            ��������
*****************************************************************
*/
void delay(rt_uint32_t count);



/*
*****************************************************************
    * @brief main����
    * @param ��
    * @retval ��
    *
    * @attention
    *************************************************************
    */
int main(void)
{
	/* Ӳ����ʼ�� */
	/* ��Ӳ����صĳ�ʼ�����������������������û����س�ʼ������ */

	/* ���ж� */
	rt_hw_interrupt_disable();

	/* SysTick�ж�Ƶ������ */
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

	/* ��������ʼ�� */
	rt_system_scheduler_init();

	/* ��ʼ�������߳� */
	rt_thread_idle_init();

	/* ��ʼ���߳� */
	rt_thread_init( &rt_flag1_thread,                                                   /* �߳̿��ƿ� */
	                "flag1_thread",                                                     /* �߳����֣��ַ�����ʽ */
	                flag1_thread_entry,                                                 /* �߳���ڵ�ַ */
	                RT_NULL,                                                            /* �߳��β� */
	                &rt_flag1_thread_stack[0],                                          /* �߳�ջ��ʼ��ַ */
	                sizeof(rt_flag1_thread_stack) );                                    /* �߳�ջ��С����λΪ�ֽ� */

	/* ���̲߳��뵽�����б� */
	rt_list_insert_before( &(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist) );

	/* ��ʼ���߳� */
	rt_thread_init( &rt_flag2_thread,                                                   /* �߳̿��ƿ� */
	                "flag2_thread",                                                     /* �߳����֣��ַ�����ʽ */
	                flag2_thread_entry,                                                 /* �߳���ڵ�ַ */
	                RT_NULL,                                                            /* �߳��β� */
	                &rt_flag2_thread_stack[0],                                          /* �߳�ջ��ʼ��ַ */
	                sizeof(rt_flag2_thread_stack) );                                    /* �߳�ջ��С����λΪ�ֽ� */
	/* ���̲߳��뵽�����б� */
	rt_list_insert_before( &(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist) );

	/* ����ϵͳ������ */
	rt_system_scheduler_start();
//  return 0;
}

/*
*************************************************************************
*                               ����ʵ��
*************************************************************************
*/
/* �����ʱ */
void delay (rt_uint32_t count)
{
	for (; count != 0; count--);
}

rt_base_t level0;
rt_uint8_t g_val = 0;

/* �߳�1 */
void flag1_thread_entry(void *p_arg)
{

	for (;;)
	{
#if 0
		flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);

		/* �߳��л����������ֶ��л� */
		rt_schedule();
#else
		flag1 = 1;
		rt_thread_delay(5);
		flag1 = 0;
		rt_thread_delay(5);
#endif
	}
}

/* �߳�2 */
void flag2_thread_entry(void *p_arg)
{
	for (;;)
	{
#if 0
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);

		/* �߳��л����������ֶ��л� */
		rt_schedule();
#else
		flag2 = 1;
		rt_thread_delay(2);
		flag2 = 0;
		rt_thread_delay(2);
#endif
	}
}

void SysTick_Handler(void)
{
	/* �����ж� */
	rt_interrupt_enter();
	/* ʱ������ */
	rt_tick_increase();

	/* �뿪�ж� */
	rt_interrupt_leave();
}


