# Add the executable for the tests
set(SOURCES
    TestMain.cpp
    TestListElement.cpp
    TestLinkedList.cpp
    TestQueue.cpp
)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add the test executable
add_executable(tests ${SOURCES})

target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Link the gtest libraries to the test executable
target_link_libraries(tests gtest gtest_main)