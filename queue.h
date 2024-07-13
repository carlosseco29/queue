#ifndef QUEUE_H
#define QUEUE_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "Exceptions.h"
#include "QueueElement.h"

//TODO
//Queue passa a implementar o getBlocking
//Class LinkedList passa a tratar dos pushs e pops
template <class T>
class Queue {
public:
    Queue(int size);
    //Queue(const Queue&) = delete; //TODO implement safe copy constructor
    //Queue& operator=(const Queue&) = delete; //TODO implemente safe copy assignment operator
    void Push(T element);
    T Pop();
    T PopWithTimeout(int milliseconds);
    int Count();
    int Size();

private:
    T _GetElementBlocking(int timeoutMilliseconds = 0);
    T _Pop();
    QueueElement<T>* _firstElement = nullptr;
    QueueElement<T>* _lastElement = nullptr;
    std::mutex _mutex;
    const int _size;
    int _count = 0;
    const int _millisecondsDefaultPollingPeriod = 100;   
};

template <class T>
Queue<T>::Queue(int size) : _size(size){
    if (_size <= 0) {
        throw InvalidQueueSizeException("Queue can't have a size lower than or equal to 0.");
    }
};

template <class T>
void Queue<T>::Push(T element){
    std::lock_guard<std::mutex> lockGuard(_mutex);
    if (_firstElement == nullptr){
        _firstElement = new QueueElement<T>(element);
        _lastElement = _firstElement;
    } else {
        _lastElement->nextElement = new QueueElement<T>(element);
        _lastElement = _lastElement->nextElement;
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
    //TODO Document that this function is not thread safe and 
    //that synchronization must be ensured before calling it.
    //It also should not be called on an empty queue!
    T element = _firstElement->element;
    QueueElement<T>* newFirstElement = _firstElement->nextElement;
    delete _firstElement;
    _firstElement = newFirstElement;
    
    _count--;
    return element;
}

template <class T>
T Queue<T>::_GetElementBlocking(int timeoutMilliseconds){
    int millisecondsToWait = _millisecondsDefaultPollingPeriod;
    int waitedMilliseconds = 0;
    int millisecondsToTimeout = timeoutMilliseconds;

    while(true) {
        std::unique_lock<std::mutex> uniqueLock(_mutex);
        if (_count > 0) {
            return _Pop();
        } else {
            uniqueLock.unlock();
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
            std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToWait));
        }
    }
}

template <class T>
int Queue<T>::Count(){
    std::lock_guard<std::mutex> lockGuard(_mutex);
    return _count;
}

template <class T>
int Queue<T>::Size(){
    return _size;
}

#endif //QUEUE_H