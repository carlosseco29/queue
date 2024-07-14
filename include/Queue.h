#ifndef QUEUE_H
#define QUEUE_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "Exceptions.h"
#include "ListElement.h"
#include "LinkedList.h"

template <class T>
class Queue {
public:
    Queue() = delete;
    Queue(int size);
    Queue(const Queue& other) = delete;
    Queue(Queue& other);
    Queue& operator=(Queue&) = default;
    void Push(T element);
    T Pop();
    T PopWithTimeout(int milliseconds);
    int Count();
    int Size();

private:
    LinkedList<int> linkedList;
    T _GetElementBlocking(int timeoutMilliseconds = 0);
    T _Pop();    
    mutable std::recursive_mutex _mutex;
    const int _size;
    int _count = 0;
    const int _millisecondsDefaultPollingPeriod = 100;
    ListElement<T>* _lastElement = nullptr;
};

template <class T>
Queue<T>::Queue(int size) : _size(size){
    if (_size <= 0) {
        throw InvalidQueueSizeException("Queue can't have a size lower than or equal to 0.");
    }
}
template <class T>
Queue<T>::Queue(Queue & other) : _size(other.Size()) {
    std::lock_guard<std::recursive_mutex> otherLockGuard(other._mutex);
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    this->_count = other._count;
    this->linkedList = other.linkedList;
    if (other.linkedList.Empty()){
        return;
    }
    
    this->_lastElement = linkedList.Front();
    while(this->_lastElement->GetNext() != nullptr) {
        this->_lastElement = this->_lastElement->GetNext();
    }
};

template <class T>
void Queue<T>::Push(T element){
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    if (linkedList.Empty()){
        linkedList.InsertAfter(linkedList.GetBeforeBegin(), element);
        _lastElement = linkedList.Front();

    } else {
        linkedList.InsertAfter(_lastElement, element);
        _lastElement = _lastElement->GetNext();
    }

    _count++;
    if (_count > _size) {
        _Pop();
    }
}

template <class T>
T Queue<T>::Pop(){
    return _GetElementBlocking();
}

template <class T>
T Queue<T>::PopWithTimeout(int timeoutMilliseconds){
    return _GetElementBlocking(timeoutMilliseconds);
}

template <class T>
T Queue<T>::_Pop(){
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    _count--;
    return linkedList.PopFront();
}

template <class T>
T Queue<T>::_GetElementBlocking(int timeoutMilliseconds){
    
    int millisecondsToWait = _millisecondsDefaultPollingPeriod;
    int waitedMilliseconds = 0;
    int millisecondsToTimeout = timeoutMilliseconds;

    while(true) {

        {std::lock_guard<std::recursive_mutex> lockGuard(_mutex);

        if (_count > 0) {
            return _Pop();
        } else {
            std::cout<< "Pop thread blocked waiting for value..." << std::endl;
            if(timeoutMilliseconds > 0) {
                if (millisecondsToTimeout == 0) {
                    std::cout<<"Timeout " << timeoutMilliseconds << " reached. Waited "
                        << waitedMilliseconds << "ms" << std::endl;
                    throw TimeoutException("Timeout reached while waiting for new elements.");
                }
                
                if (millisecondsToTimeout < millisecondsToWait) {
                    millisecondsToWait = millisecondsToTimeout;
                }
                millisecondsToTimeout -= millisecondsToWait;
                waitedMilliseconds += millisecondsToWait;
            }
        }
        };
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToWait));

    }
}

template <class T>
int Queue<T>::Count() {
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    return _count;
}

template <class T>
int Queue<T>::Size() {
    return _size;
}

#endif //QUEUE_H