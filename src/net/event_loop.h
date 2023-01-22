#pragma once

#include <memory>
#include <vector>

class Channel;
class Poller;

class EventLoop {
 public:
  EventLoop();
  ~EventLoop();
  EventLoop(const EventLoop&) = delete;
  EventLoop operator=(const EventLoop&) = delete;
  EventLoop(const EventLoop&&) = delete;
  EventLoop operator=(const EventLoop&&) = delete;

  void Loop();
  void UpdateChannel(Channel*);
  void Stop();

 private:
  bool running_;
  std::unique_ptr<Poller> poller_;
  std::vector<Channel*> active_chans_{};
};