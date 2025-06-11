#ifndef STATE_DEF_H
#define STATE_DEF_H

// 状态定义
typedef enum {
	STATE_IDLE,		// 状态IDLE
	STATE_WORKING,	// 状态WORKING
	STATE_ERROR,	// 状态ERROR
	STATE_NUM 		// 状态总数
} State;

// 事件
typedef enum {
	EVENT_START,	// 事件START
	EVENT_STOP,		// 事件STOP
	EVENT_ERROR,	// 事件ERROR
	EVENT_RESET,	// 事件RESET
	EVENT_NUM		// 事件总数
} Event;

// 指向动作函数的指针
// 模仿注册-回调机制，传入任意类型的指向数据的指针（指向一个结构体）
typedef void (*StateHandler)(void *);

// 状态转移表结构体
typedef struct {
	State next_state;       // 接收到该事件后，转移到哪个状态
	StateHandler action;    // 要执行的动作
} Transition;

#endif
