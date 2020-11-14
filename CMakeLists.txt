cmake_minimum_required(VERSION 3.17)
project(Threads C)

set(CMAKE_C_STANDARD 11)

add_executable(Threads main.c threads1.c threads2.c passingArguments.c waitingThreads.c threads3.c)