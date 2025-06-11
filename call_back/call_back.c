#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义一个通用的回调函数类型（带 void* 用户数据）
typedef void (*TimerCallback)(void* user_data);

// 用户注册的数据结构
typedef struct {
    TimerCallback callback;
    void* user_data;
} TimerEvent;

// 模拟触发器，触发时执行回调
void trigger_timer(TimerEvent* evt) {
    if (evt && evt->callback) {
        evt->callback(evt->user_data);  // 调用回调函数，传入用户数据
    }
}

// === 用户自定义数据结构 ===
typedef struct {
    char name[32];
    int count;
} MyContext;

// === 用户定义的回调函数 === 
//! 用户定义的函数类型必须和中间层定义的函数类型一致！！！(void* user_data)，但是需要在内部转化为自己定义的数据指针类型（只有这样才能范围到上下文数据）
void my_timer_handler(void* user_data) {
    MyContext* ctx = (MyContext*)user_data;  // 强制转换回用户的真实类型
    ctx->count++;
    printf("Timer fired! Name = %s, Count = %d\n", ctx->name, ctx->count);
}

int main() {
    // 初始化用户数据
    MyContext ctx;
    strcpy(ctx.name, "MyTimer");
    ctx.count = 0;

    // 注册事件
    TimerEvent evt;
    evt.callback = my_timer_handler;
    evt.user_data = &ctx;

    // 触发三次定时器
    trigger_timer(&evt);
    trigger_timer(&evt);
    trigger_timer(&evt);

    return 0;
}

/*
你举得这个例子太好了，非常好的说明了，在不确定用户向这个回调函数传入的是什么类型的数据，以及执行什么样的函数的时候。上层开发给下层一个接口
typedef struct {
    TimerCallback callback;
    void* user_data;
} TimerEvent;      TimerEvent evt;就是告诉用户，需要向这个evt中的callback和user_data指定数据，
 一个是定时到时执行的函数，一个是函数执行会用到的数据。但是由于不知道是什么数据，所以用了void* user_data。
 这个user_data其实就是用户类的this指针。还有一个就是执行的函数。
 下层在注册的时候需要注意，因为下层要实现这个函数，要利用user_data数据，
 而TimerCallback callback的类型是typedef void (*TimerCallback)(void* user_data)。
 为了能够正确使用user_data数据，就需要把他转化为自己可以使用的指针类型，也就是this指针。
*/
