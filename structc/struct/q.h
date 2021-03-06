﻿#ifndef _H_Q
#define _H_Q

#include "struct.h"

//
// pop empty  <=> tail == -1 ( head == 0 )
// push full  <=> head == tail + 1
//
typedef struct q {
    int head;           // 头结点
    int tail;           // 尾结点
    int size;           // 队列大小
    void ** queue;      // 队列实体
} q_t[1];

//
// q_init - 初始化
// q      : 队列对象
// return : void
// INT_Q  - 队列初始大小, 必须是 2 的幂
#define INT_Q     (1<<6)
inline void q_init(q_t q) {
    q->head = 0;
    q->tail = -1;
    q->size = INT_Q;
    q->queue = malloc(sizeof(void *) * INT_Q);
}

//
// q_swap - q swap
// r      : q one
// w      : q two
// return : void
//
inline void q_swap(q_t r, q_t w) {
    q_t q;
    q[0] = r[0];
    r[0] = w[0];
    w[0] = q[0];
}

//
// q_pop - 队列中弹出消息数据
// q      : 队列对象
// return : 若队列 empty, 返回 NULL
//
inline void * q_pop(q_t q) {
    void * m = NULL;
    if (q->tail >= 0) {
        m = q->queue[q->head];
        if (q->tail != q->head)
            q->head = (q->head + 1) & (q->size - 1);
        else {
            q->head = 0; // empty 情况, 重置 tail and head
            q->tail = -1;
        }
    }
    return m;
}

//
// q_delete - 队列销毁
// q        : 队列对象
// fdie     : push 节点删除行为
// return   : void
//
extern void q_delete(q_t q, node_f fdie);

//
// q_push - 队列中压入数据
// q      : 队列对象
// m      : 压入消息
// return : void
// 
extern void q_push(q_t q, void * m);

#endif//_H_Q
