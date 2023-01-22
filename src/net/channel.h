#pragma once

#include <sys/event.h>

#include <functional>
class EventLoop;

class Channel {
 public:
  // TODO: why this signature?
  using IOCallback = std::function<void()>;

 public:
  Channel(int fd,EventLoop* loop,bool is_timer = false);
  Channel(const Channel&) = delete;
  Channel operator=(const Channel&) = delete;
  Channel(const Channel&&) = delete;
  Channel operator=(const Channel&&) = delete;

  void HandleEvent();

  void set_read_enabled();
  void set_write_enabled();
  void unset_read_enabled();
  void unset_write_enabled();
  void set_read_callback(IOCallback cb);
  void set_write_callback(IOCallback cb);
  bool read_enabled() const { return read_enabled_; }
  bool write_enabled() const { return write_enabled_; }
  void mark_read() { can_read_ = true; }
  void mark_write() { can_write_ = true; }
  int get_fd() const { return fd_; }
  int get_idx() const { return idx_; }
  void set_idx(int idx) { idx_ = idx; }

  void set_timer(int microseconds) { microseconds_ = microseconds; }
  int get_timer() const { return microseconds_; }
  bool is_timer() const { return is_timer_; }

 private:
  void update();

 private:
  int fd_ = 0;
  int idx_ = -1;
  bool read_enabled_ = false;
  bool write_enabled_ = false;
  bool can_read_ = false;
  bool can_write_ = false;
  IOCallback read_cb_{};
  IOCallback write_cb_{};
  EventLoop* loop_{};

  bool is_timer_ = false;  // TODO(fangliming): support more timer.
  int microseconds_ = 0;
};