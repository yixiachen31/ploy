#include "state_def.h"
#include "action_func.h"

#define NULL ((void *)0)

// 引用全局变量
extern Transition state_table[STATE_NUM][EVENT_NUM];

// 局部函数(状态机的核心函数)
// 负责处理状态切换，并执行相关动作
static void handle_event(Event event);

// 全局变量
// 当前状态
State current_state = STATE_IDLE;

int main() {
	handle_event(EVENT_START);  // IDLE -> WORKING
	handle_event(EVENT_ERROR);  // WORKING -> ERROR
	handle_event(EVENT_RESET);  // ERROR -> IDLE
	handle_event(EVENT_STOP);   // IDLE -> IDLE (无动作)
	return 0;
}

static void handle_event(Event event) {
	Transition t = state_table[current_state][event];
	
	// 先执行动作，再转移状态。“有点类似于Mealy型状态机”
	if (t.action) {
		t.action(NULL);  // 执行转移动作
	}
	current_state = t.next_state;
}
