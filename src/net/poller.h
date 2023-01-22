#pragma once
#include <sys/event.h>

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "channel.h"

class Poller {
 public:
  Poller();
  Poller(const Poller&) = delete;
  Poller operator=(const Poller&) = delete;
  Poller(const Poller&&) = delete;
  Poller operator=(const Poller&&) = delete;

  void Poll(std::vector<Channel*>* active_chan);
  void UpdateChannel(Channel* chan);

 private:
  void fillActiveChannel(struct kevent* events, int nve,
                         std::vector<Channel*>* chan_vec_ptr);

 private:
  std::vector<struct kevent> kevents_{};
  int kqueue_fd_ = -1;
  int num_of_fd_ = 0;

  // Record the channel and kevent info.
  std::unordered_map<int, Channel*> m_fd2chan_{};
};