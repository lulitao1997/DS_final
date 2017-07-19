cmake_minimum_required(VERSION 3.6)
project(Topic_A)

set(CMAKE_CXX_STANDARD 11)

set(TOPIC_A Topic_A.cpp read.h all.h point.h road.h graph.h block.h order.h)
set(TOPIC_B Topic_B.cpp wread.h read.h all.h point.h road.h graph.h block.h restaurant.h order.h)
add_executable(Topic_A ${TOPIC_A})
add_executable(Topic_B ${TOPIC_B})
