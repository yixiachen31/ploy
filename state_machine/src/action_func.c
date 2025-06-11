#include "action_func.h"
#include <stdio.h>

void action_start(void * p_data) {
    printf("启动系统\n");
}
void action_stop(void * p_data) {
    printf("停止系统\n");
}
void action_error(void * p_data) {
    printf("系统出错\n");
}
void action_reset(void * p_data) {
    printf("错误已复位，回到IDLE\n");
}
void action_none(void * p_data) {
    // 无操作
}
