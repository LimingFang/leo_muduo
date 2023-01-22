set(net_SRCS
  event_loop.cc
  channel.cc
  poller.cc
  )
  
set(net_HEADERS
  event_loop.h
  channel.h
  poller.h
  )
  
add_library(muduo_net ${net_SRCS})
add_subdirectory(tests)