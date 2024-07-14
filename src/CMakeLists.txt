# Add the executable for the main project
add_executable(queue main.cpp queue.cpp)

target_include_directories(queue PRIVATE ${PROJECT_SOURCE_DIR}/../include)

find_package(Threads REQUIRED)
target_link_libraries(queue Threads::Threads)