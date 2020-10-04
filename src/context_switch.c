#include "context_switch.h"

void wait_context_switch(void)
{
    while(1){1 == 1;}
}

void context_switch(int sig)
{   
    global_tcb_group->current_thread_id++;
    global_tcb_group->current_thread_id = (global_tcb_group->current_thread_id % global_tcb_group->alloc_thread_id);
    global_tcb_group->next_tcb = global_tcb_group->tcb_list[global_tcb_group->current_thread_id];
    alarm(1);
    setcontext(&(global_tcb_group->next_tcb->context));
}

void init()
{
    global_tcb_group = (thread_control_block_group*)calloc(sizeof(thread_control_block_group), 1);
    global_tcb_group->alloc_thread_id = 0;
    global_tcb_group->current_thread_id = 0;
    signal(SIGALRM, context_switch);
}

void start(void)
{
    assert(global_tcb_group->alloc_thread_id >= 1);
    global_tcb_group->current_thread_id = -1;
    alarm(1);
    wait_context_switch();
}

thread_control_block* new_thread_control_block(void (*ptr_runtime)(void*), void *argument, void* return_val)
{
    assert(global_tcb_group->alloc_thread_id < (thread_total - 1));
    thread_control_block *new_thread_control_block_struct = (thread_control_block*)calloc(sizeof(thread_control_block), 1);
    new_thread_control_block_struct->thread_id = (global_tcb_group->alloc_thread_id++);
    new_thread_control_block_struct->ptr_runtime = ptr_runtime;
    new_thread_control_block_struct->argument = argument;
    new_thread_control_block_struct->return_val = return_val;
    // context
    getcontext(&(new_thread_control_block_struct->context));
    uint8_t *stack = (uint8_t*)calloc(sizeof(uint8_t), 4096);
    new_thread_control_block_struct->context.uc_stack.ss_sp = stack;
    new_thread_control_block_struct->context.uc_stack.ss_size = sizeof(uint8_t) * 4096;
    makecontext(&(new_thread_control_block_struct->context), (void*)ptr_runtime, 0);
    return new_thread_control_block_struct;
}

void tcb_into_group(thread_control_block* thread_control_block_device)
{
    global_tcb_group->tcb_list[thread_control_block_device->thread_id] = thread_control_block_device;
}
