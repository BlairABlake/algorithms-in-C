cmake_minimum_required(VERSION 3.25)
project(MyAlgorithms C)

set(CMAKE_C_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/)

add_library(MyAlgorithms list.c htable.c htable.h stack.c stack.h queue.c queue.h tree.c tree.h binary_search.c binary_search.h heap.c heap.h graph.c graph.h set.c set.h)
add_library(munit deps/munit/munit.c)

add_executable(test test/test.c test/test_htable.h test/test_stack.h test/test_queue.h test/test_tree.h test/test_binary_search.h test/test_heap.h test/test_graph.h)
target_link_libraries(test munit MyAlgorithms)
