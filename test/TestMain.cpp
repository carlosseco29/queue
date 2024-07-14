#include <gtest/gtest.h>


/// @brief Main function for the test executable
/// @param argc number of args
/// @param argv pointer to the first arg
/// @return the result of RUN_ALL_TESTS(); from gtest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}