#include <iostream>
#include <thread>
#include "Queue.h"


//TODO decide if I should create interfaces for the classes
int main() {
    Queue<int> qs(2);

    std::cout << "size is " << qs.Size() << std::endl;
    std::cout << "count is " << qs.Count() << std::endl;

    
    try {
        qs.PopWithTimeout(1);
    } catch (TimeoutException e) {
        std::cout << "Got exception 1!" << std::endl;
    }
    try {
        qs.PopWithTimeout(99);
    } catch (TimeoutException e) {
        std::cout << "Got exception 2!" << std::endl;
    }
    try {
        qs.PopWithTimeout(100);
    } catch (TimeoutException e) {
        std::cout << "Got exception 3!" << std::endl;
    }
    try {
        qs.PopWithTimeout(101);
    } catch (TimeoutException e) {
        std::cout << "Got exception 4!" << std::endl;
    }
    try {
        qs.PopWithTimeout(199);
    } catch (TimeoutException e) {
        std::cout << "Got exception 5!" << std::endl;
    }
    try {
        qs.PopWithTimeout(200);
    } catch (TimeoutException e) {
        std::cout << "Got exception 6!" << std::endl;
    }
    try {
        qs.PopWithTimeout(201);
    } catch (TimeoutException e) {
        std::cout << "Got exception 7!" << std::endl;
    }

    try {
        qs.PopWithTimeout(299);
    } catch (TimeoutException e) {
        std::cout << "Got exception 8!" << std::endl;
    }

    try {
        qs.PopWithTimeout(300);
    } catch (TimeoutException e) {
        std::cout << "Got exception 9!" << std::endl;
    }

    try {
        qs.PopWithTimeout(301);
    } catch (TimeoutException e) {
        std::cout << "Got exception 10!" << std::endl;
    }

    std::cout << "pushing 1" << std::endl;
    qs.Push(1);
    std::cout << "after push" << std::endl;
    std::cout<< "Popped: " << qs.Pop() << std::endl;
    std::cout << "pushing 2" << std::endl;
    qs.Push(2);
    std::cout << "pushing 3" << std::endl;
    qs.Push(3);
    std::cout << "pushing 4" << std::endl;
    qs.Push(4);
    std::cout<< "Popped: " << qs.Pop() << std::endl;
    std::cout<< "Popped: " << qs.Pop() << std::endl;

    std::thread PushThread([&qs](){
        std::cout << "Push thread launched. Going to sleep 300 ms..." <<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Push thread slept. Going to push value" <<std::endl;
        qs.Push(5);
    });

    std::cout << "Going to block waiting to pop" << std::endl;
    std::cout<< "Popped: " << qs.Pop() << std::endl;
    std::cout<< "Popped: " << qs.Pop() << std::endl;

    PushThread.join();
    return 0;
}
