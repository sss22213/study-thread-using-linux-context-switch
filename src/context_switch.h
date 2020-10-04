#ifndef _context_switch_h_
#define _context_switch_h_
#include <ucontext.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#define thread_total 20
typedef struct thread_control_block_group thread_control_block_group;
typedef struct thread_control_block thread_control_block;
typedef struct thread_control_block
{
    uint8_t thread_id;
    ucontext_t context;
    void (*ptr_runtime)(void*);
    void *argument;
    void *return_val;
}thread_control_block;

typedef struct thread_control_block_group
{
    thread_control_block *tcb_list[thread_total];
    thread_control_block *next_tcb;
    uint8_t alloc_thread_id;
    uint8_t current_thread_id;
}thread_control_block_group;

void init();
thread_control_block* new_thread_control_block(void (*)(void*), void*, void*);
void tcb_into_group(thread_control_block*);
thread_control_block_group *global_tcb_group;
void start(void);
void context_switch(int);
void wait_context_switch(void);

#endif