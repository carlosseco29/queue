#include "Queue.h"

template <class T>
Queue<T>::Queue(int size) : _size(size){
    if (_size < 1) {
        throw InvalidQueueSizeException("Queue can't have a size lower than or equal to 0.");
    }
}

template <class T>
Queue<T>::Queue(const Queue & other) : _size(other._size) {
    _Copy(other);
};

template <class T>
Queue<T> &Queue<T>::operator=(const Queue &other) {
    if (this != &other) {
        _Copy(other);
    }
    return *this;
};

template <class T>
void Queue<T>::_Copy(const Queue<T> &other) {
    std::lock_guard<std::recursive_mutex> otherLockGuard(other._mutex);
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    this->_count = other._count;
    this->_size = other._size;
    this->linkedList = other.linkedList;
    if (other.linkedList.Empty()){
        this->_lastElement = nullptr;
        return;
    }
    
    this->_lastElement = this->linkedList.Begin();
    while(this->_lastElement->GetNext() != nullptr) {
        this->_lastElement = this->_lastElement->GetNext();
    }
}

template <class T>
void Queue<T>::Push(T element){
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    if (linkedList.Empty()){
        linkedList.InsertAfter(linkedList.GetBeforeBegin(), element);
        _lastElement = linkedList.Begin();
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
T Queue<T>::_GetElementBlocking(int timeoutMilliseconds){
    int millisecondsToWait = _millisecondsDefaultPollingPeriod;
    int millisecondsToTimeout = timeoutMilliseconds;
    while(true) {
        {
            std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
            if (_count > 0) {
                return _Pop();
            }
        }    
        if(timeoutMilliseconds > 0) {
            if (millisecondsToTimeout == 0) {
                throw TimeoutException("Timeout reached while waiting for new elements.");
            }
            if (millisecondsToTimeout < millisecondsToWait) {
                millisecondsToWait = millisecondsToTimeout;
            }
            millisecondsToTimeout -= millisecondsToWait;
        }
        std::cout<< "Pop blocked. Sleeping for " << millisecondsToWait << " ms"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToWait));
    }
}

template <class T>
T Queue<T>::_Pop(){
    _count--;
    return linkedList.PopFront();
}

template <class T>
T Queue<T>::PopWithTimeout(int timeoutMilliseconds){
    return _GetElementBlocking(timeoutMilliseconds);
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