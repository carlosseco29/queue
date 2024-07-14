#ifndef QUEUE_H
#define QUEUE_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "Exceptions.h"
#include "ListElement.h"
#include "LinkedList.h"

/// @brief A templated class for a queue
///
/// Container for T values offering push, pop and pop with timeout operations and automatic
/// resize when the maximum size is reached, discarding the oldest items
/// @tparam T The type of values that the queue will hold 
template <class T>
class Queue {
public:
    /// @brief Default constructor deleted, maximum queue size is mandatory
    Queue() = delete;

    /// @brief A constructor for the Queue
    ///
    /// This constructor initializes a Queue with provided maximum size
    ///
    /// @param value to initialize the first element of the list with
    /// @throws InvalidQueueSizeException if a queue tries to be created with \param size < 1
    Queue(int size);

    /// @brief The copy constructor for the Queue
    ///
    /// This constructor creates a new Queue as a copy of the given one
    /// 
    /// @param other the Queue object to copy from
    Queue(const Queue& other);
    
    /// @brief The assignment operator for the Queue class
    ///
    /// This operator assigns the content of another Queue to the current object
    //
    /// @param other the Queue object to assign from
    ///
    /// @return A reference to the element Queue object after assignment.
    Queue& operator=(const Queue& other);

    /// @brief Adds a nem element to the queue
    ///
    /// @param element to add to the queue
    void Push(T element);
    
    /// @brief Blocks untill an item is available in the queue and returns it
    ///
    /// Will block forever if no new pushes happen
    ///
    /// @return The value of the element poped from the queue
    T Pop();
    
    /// @brief Blocks untill an item is available or for a maximum of \param milliseconds ms
    ///
    /// Waits for a maximum of \param milliseconds in order to return it. If timeout is reached 
    /// a TimeoutException will be thrown
    ///
    /// @param milliseconds number of ms to wait before timing out
    /// @return the value poped from the list
    /// @throws TimeoutException if timeout is reached and value is available
    T PopWithTimeout(int milliseconds);

    /// @brief Gets the number of elements in the queue
    /// @return the number of elements in the queue
    int Count();

    /// @brief Gets the maximum size of the queue
    /// @return the maximum size of the Queue
    int Size();

private:
    /// @brief The linked list where the queue elements are stored
    LinkedList<int> linkedList;
    
    /// @brief Block for a maximum of \param timeoutMillisenconds or untill an element is available
    ///
    /// If no pushes ever happen, it will block forever
    ///
    /// @param timeoutMilliseconds the ms to timeout after
    /// @return the element, if it is available
    /// @throws TimeoutException if timeout is reached and no value is available
    T _GetElementBlocking(int timeoutMilliseconds = 0);
    
    /// @brief Calls PopFront on the linked list
    ///
    /// Causes InvalidPopUseException if called on an empty list. To be used carefully.
    ///
    /// @return The poped value
    /// @throws InvalidPopUseException if Pop is called on an empty list
    T _Pop();    
    
    /// @brief A mutex to protect list operations
    mutable std::recursive_mutex _mutex;

    /// @brief the maximum size of the queue
    int _size;

    /// @brief The number of elements in the queue
    int _count = 0;

    /// @brief The default number of ms to poll when blocked, waiting to pop
    const int _millisecondsDefaultPollingPeriod = 100;
    
    /// @brief the last element of the list
    ListElement<T>* _lastElement = nullptr;

    /// @brief A method which copies the values in other to the current object
    ///
    /// @param other the LinkedList object to copy from
    void _Copy(const Queue<T> &other);

};

#include "../src/Queue.tpp"

#endif //QUEUE_H