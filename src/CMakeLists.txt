set(SOURCES
    main.cpp
    ListElement.tpp
    LinkedList.tpp
    Queue.tpp
)

add_executable(queue ${SOURCES})
include_directories(${PROJECT_SOURCE_DIR}/include)

target_include_directories(queue PRIVATE ${PROJECT_SOURCE_DIR}/src)

find_package(Threads REQUIRED)
target_link_libraries(queue PRIVATE Threads::Threads)