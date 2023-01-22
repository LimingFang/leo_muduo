#include "event_loop.h"

#include <assert.h>

#include "channel.h"
#include "poller.h"

thread_local EventLoop* g_loop = nullptr;
EventLoop::EventLoop() : poller_(new Poller()), running_(false) {
  assert(g_loop == nullptr);
  g_loop = this;
}

EventLoop::~EventLoop() { assert(!running_); }

void EventLoop::Loop() {
  running_ = true;
  while (running_) {
    active_chans_.clear();
    poller_->Poll(&active_chans_);
    for (auto chan : active_chans_) {
      chan->HandleEvent();
    }
  }
}

void EventLoop::UpdateChannel(Channel *chan) { poller_->UpdateChannel(chan); }

void EventLoop::Stop() { running_ = false; }