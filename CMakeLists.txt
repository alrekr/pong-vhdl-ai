cmake_minimum_required(VERSION 2.8)
project (AI)
add_executable(ai main.cpp)
# add_executable(tester main2.cpp)

# The following definition enables Debug mode in the code with terminal output
add_definitions(-DDEBUG)

# The following definition enables Production mode in the code; this is what
# is needed for actual MicroBlaze use
#add_definitions(-DPROD)
