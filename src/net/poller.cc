#include "poller.h"

#include <cassert>

#include "channel.h"

Poller::Poller() {
  kqueue_fd_ = kqueue();
  if (kqueue_fd_ == -1) {
    assert(false);
  }
}

void Poller::Poll(std::vector<Channel*>* active_chan) {
  struct kevent events[num_of_fd_];
  int nve = kevent(kqueue_fd_, kevents_.data(), kevents_.size(), events,
                   num_of_fd_, nullptr);
  if (nve > 0) {
    fillActiveChannel(events, nve, active_chan);
  }
}

void Poller::fillActiveChannel(struct kevent* events, int nve,
                               std::vector<Channel*>* chan_vec_ptr) {
  for (int i = 0; i < nve; i++) {
    int fd = events[i].ident;
    Channel* chan = m_fd2chan_[fd];
    if (events[i].filter & EVFILT_TIMER) {
      chan->mark_read();
      chan_vec_ptr->emplace_back(chan);
      continue;
    }
    if (events[i].filter & EVFILT_READ) {
      chan->mark_read();
    }
    if (events[i].filter & EVFILT_WRITE) {
      chan->mark_write();
    }
    chan_vec_ptr->emplace_back(chan);
  }
}

void Poller::UpdateChannel(Channel* chan) {
  int fd = chan->get_fd();
  bool is_exist = m_fd2chan_.count(fd) > 0;
  int filter = 0;
  int flag = EV_ADD;
  int fflag = 0;
  int data = 0;
  if (chan->is_timer()) {
    filter = EVFILT_TIMER;
    fflag = NOTE_USECONDS;
    data = chan->get_timer();
  } else {
    flag |= EV_ONESHOT;
    if (chan->read_enabled()) {
      filter |= EVFILT_READ;
    }
    if (chan->write_enabled()) {
      filter |= EVFILT_WRITE;
    }
  }
  if (is_exist) {
    auto idx = chan->get_idx();
    auto& event = kevents_[idx];
    EV_SET(&event, fd, filter, flag, fflag, data, 0);
  } else {
    chan->set_idx(kevents_.size());
    struct kevent event {};
    EV_SET(&event, fd, filter, flag, fflag, data, 0);
    kevents_.push_back(event);
    num_of_fd_++;
    m_fd2chan_[fd] = chan;
  }
}