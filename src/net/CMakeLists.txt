set(net_SRCS
  event_loop.cc
  )
  
set(net_HEADERS
  event_loop.h  
  )
  
add_library(muduo_net ${net_SRCS})
