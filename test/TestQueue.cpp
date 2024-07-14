#include <gtest/gtest.h>
#include <future>

#include "Queue.h"

template <typename Func>
bool isBlocking(Func func, Queue<int> &queue, std::chrono::milliseconds timeout) {
    auto future = std::async(std::launch::async, func);
    // Check if the method completes within the timeout
    if (future.wait_for(timeout) == std::future_status::timeout) {
        queue.Push(0);
        // The method is blocking (did not complete within the timeout)
        return true;
    } else {
        // The method is not blocking (completed within the timeout)
        return false;
    }
}

/// @brief Tests the copy constructor 
TEST(QueueTest, Copy) {
    Queue<int> queue(5);

    queue.Push(0);
    Queue<int> queueCopy = queue;
    EXPECT_EQ(queue.Size(), queueCopy.Size());
    queueCopy.Push(1);
    queueCopy.Push(2);
    queueCopy.Push(3);
    EXPECT_EQ(queueCopy.Pop(), 0);
    EXPECT_EQ(queue.Count(), 1);
    queue.Push(3);
    EXPECT_EQ(queue.Count(), 2);
    EXPECT_EQ(queueCopy.Count(), 3);
    EXPECT_EQ(queue.Pop(), 0);
    EXPECT_EQ(queue.Pop(), 3);
    EXPECT_EQ(queue.Count(), 0);

    EXPECT_EQ(queueCopy.Count(), 3);
    EXPECT_EQ(queueCopy.Pop(), 1);
    EXPECT_EQ(queueCopy.Pop(), 2);
    EXPECT_EQ(queueCopy.Pop(), 3);
}

/// @brief Tests the copy constructor on an empty queue
TEST(QueueTest, CopyEmpty) {
    Queue<int> queue(2);    
    Queue<int> queueCopy(queue);
    queueCopy.Push(0);
    queueCopy.Push(1);
    queue.Push(2);
    EXPECT_EQ(queue.Size(), queueCopy.Size());
    EXPECT_EQ(queue.Count(), 1);
    EXPECT_EQ(queueCopy.Count(), 2);
    EXPECT_EQ(queue.Pop(), 2);
    EXPECT_EQ(queueCopy.Pop(), 0);
    EXPECT_EQ(queueCopy.Pop(), 1);
}

/// @brief Tests the push method on an empty queue
TEST(QueueTest, PushEmtpy) {
    Queue<int> queue(2);    
    queue.Push(0);
    EXPECT_EQ(queue.Count(), 1);
    queue.Push(1);
    EXPECT_EQ(queue.Count(), 2);
}

/// @brief Tests the push method on queue with values
TEST(QueueTest, Push) {
    Queue<int> queue(2);    
    queue.Push(0);
    EXPECT_EQ(queue.Count(), 1);
    queue.Push(1);
    EXPECT_EQ(queue.Count(), 2);
}

/// @brief Tests the resize mechanism when max size is reached
TEST(QueueTest, PushToOverflow) {
    Queue<int> queue(2);    
    queue.Push(0);
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    queue.Push(4);
    queue.Push(5);
    EXPECT_EQ(queue.Count(), 2);
    EXPECT_EQ(queue.Pop(), 4);
    EXPECT_EQ(queue.Pop(), 5);
}

/// @brief Tests the Pop method on an empty queue
TEST(QueueTest, PopEmpty) {
    Queue<int> queue(2);
    auto timeout = std::chrono::milliseconds(500);
    EXPECT_EQ(true, isBlocking(std::bind(&Queue<int>::Pop,  &queue), queue, timeout));
}

/// @brief Tests the Pop method
TEST(QueueTest, Pop) {
    Queue<int> queue(2);
    queue.Push(0);
    queue.Pop();
    EXPECT_EQ(queue.Count(), 0);
}



/// @brief Tests the PopWithTimeout method on a queue with elements
TEST(QueueTest, PopWithTimeout) {
    Queue<int> queue(2);
    queue.Push(0);
    EXPECT_NO_THROW(queue.PopWithTimeout(1));
    EXPECT_EQ(queue.Count(), 0);
}
/// @brief Tests the PopWithTimeout method on an empty queue
TEST(QueueTest, PopWithTimeoutEmpty) {
    Queue<int> queue(2);
    EXPECT_THROW(queue.PopWithTimeout(1), TimeoutException);
    EXPECT_THROW(queue.PopWithTimeout(99), TimeoutException);
    EXPECT_THROW(queue.PopWithTimeout(100), TimeoutException);
    EXPECT_THROW(queue.PopWithTimeout(101), TimeoutException);
    EXPECT_THROW(queue.PopWithTimeout(199), TimeoutException);
    EXPECT_THROW(queue.PopWithTimeout(200), TimeoutException);
    EXPECT_THROW(queue.PopWithTimeout(201), TimeoutException);
}

/// @brief performs the exercise's test
TEST(QueueTest, ExerciseTest) {
    Queue<int> queue(2);
    queue.Push(1);
    EXPECT_EQ(queue.Pop(), 1);
    queue.Push(2);
    queue.Push(3);
    queue.Push(4);
    EXPECT_EQ(queue.Pop(), 3);
    EXPECT_EQ(queue.Pop(), 4);
    
    std::thread PushThread([&queue](){
        std::cout << "Push thread launched. Going to sleep 500 ms..." << std::endl
                  << "Pop should stay blocked" <<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Push thread slept. Going to push value" <<std::endl
                  << "Pop should unblock now" <<std::endl;
        queue.Push(5);
    });

    EXPECT_EQ(queue.Pop(), 5);
    PushThread.join();
}
