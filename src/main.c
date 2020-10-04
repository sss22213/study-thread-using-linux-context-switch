#include "context_switch.h"

void thread_1(void* argument)
{
    printf("i am thread1\n");
    wait_context_switch();
}
void thread_2(void* argument)
{
    printf("i am thread2\n");
    wait_context_switch();
}

void thread_3(void* argument)
{
    printf("i am thread3\n");
    wait_context_switch();
}

int main(int argc, char** argv)
{
    init();
    int argument = 1;
    int *return_val = (int*)calloc(sizeof(int), 1); 
    thread_control_block *tcb_1 = new_thread_control_block(thread_1, &argument, return_val);
    thread_control_block *tcb_2 = new_thread_control_block(thread_2, &argument, return_val);
    thread_control_block *tcb_3 = new_thread_control_block(thread_3, &argument, return_val);
    tcb_into_group(tcb_1);
    tcb_into_group(tcb_2);
    tcb_into_group(tcb_3);
    start();
    return 0;
}