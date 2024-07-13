cmake_minimum_required(VERSION 3.16.3)

# Set the project name
project(QueueImplementation)

# Add the executable
add_executable(queue main.cpp queue.cpp)

find_package(Threads REQUIRED)
target_link_libraries(queue Threads::Threads)