#include "event_loop.h"
#include "channel.h"
#include <iostream>

EventLoop* g_loop = nullptr;

void timer_callback(){
    std::cout<<"Timer callback!" << std::endl;
    g_loop->Stop();
}

// 定义一个 timer channel，定时触发 callback
int main(){
  EventLoop loop;
  g_loop = &loop;
  Channel chan(1,g_loop,true/* is_timer */);
  chan.set_timer(1000000);
  chan.set_read_enabled();
  chan.set_read_callback(timer_callback);
  
  g_loop->Loop();
}
