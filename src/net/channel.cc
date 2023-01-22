#include "channel.h"

#include "event_loop.h"

Channel::Channel(int fd, EventLoop* loop, bool is_timer)
    : fd_(fd), loop_(loop), is_timer_(is_timer) {}

void Channel::HandleEvent() {
  if (can_read_) {
    read_cb_();
  }
  if (can_write_) {
    write_cb_();
  }
  can_read_ = can_write_ = false;
}
void Channel::set_read_enabled() {
  read_enabled_ = true;
  update();
}
void Channel::set_write_enabled() {
  write_enabled_ = true;
  update();
}
void Channel::unset_read_enabled() {
  read_enabled_ = false;
  update();
}
void Channel::unset_write_enabled() {
  write_enabled_ = false;
  update();
}
void Channel::set_read_callback(IOCallback cb) { read_cb_ = cb; }
void Channel::set_write_callback(IOCallback cb) { write_cb_ = cb; }
void Channel::update() { loop_->UpdateChannel(this); }