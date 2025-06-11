#include "state_def.h"
#include "action_func.h"


// 全局变量，状态转移表，用于指示在当前状态下，当发生了不同的事件时，状态转移以及动作的情况
Transition state_table[STATE_NUM][EVENT_NUM] = {
    // STATE_IDLE 当前状态
    {
        {STATE_WORKING/*次态*/,	action_start/*动作*/}, 	  // EVENT_START (事件)
        {STATE_IDLE,    		action_none},  			// EVENT_STOP
        {STATE_ERROR,   		action_error}, 			// EVENT_ERROR
        {STATE_IDLE,    		action_none}   			// EVENT_RESET
    },
    // STATE_WORKING
    {
        {STATE_WORKING, 		action_none},
        {STATE_IDLE,    		action_stop},
        {STATE_ERROR,   		action_error},
        {STATE_WORKING, 		action_none}
    },
    // STATE_ERROR
    {
        {STATE_ERROR,   		action_none},
        {STATE_ERROR,   		action_none},
        {STATE_ERROR,   		action_none},
        {STATE_IDLE,    		action_reset}
    }
};

