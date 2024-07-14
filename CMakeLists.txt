cmake_minimum_required(VERSION 3.16.3)

# Set the project name
project(QueueImplementation)

# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add sources and tests
add_subdirectory(src)
add_subdirectory(test)
