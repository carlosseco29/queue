#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <limits>

#include "Exceptions.h"
#include "ListElement.h"

template <class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(const T element);
    //LinkedList(LinkedList& other);
    LinkedList(const LinkedList& other);
    //LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList& other);

    ~LinkedList();
    void InsertAfter(ListElement<T>* queueElement, T element);
    T PopFront();
    bool Empty();
    ListElement<T>* GetBeforeBegin();
    ListElement<T>* Front();

private:
    ListElement<T>* _firstElement = nullptr;
    ListElement<T>* _beforeBegin = nullptr;
    mutable std::recursive_mutex _mutex;
    void _DeleteAllElements(ListElement<T>* current = nullptr);
};

template <class T>
LinkedList<T>::LinkedList() {
    _beforeBegin = new ListElement<T>(T());
    _beforeBegin->SetBeforeBegin();
}

template <class T>
LinkedList<T>::~LinkedList() {
    delete _beforeBegin;
    _DeleteAllElements();
}

template <class T>
LinkedList<T>::LinkedList(const T element) : LinkedList() {
    InsertAfter(_beforeBegin, element);
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList &other) : LinkedList()  {
    std::lock_guard<std::recursive_mutex> otherLockGuard(other._mutex);
    std::lock_guard<std::recursive_mutex> lockGuard(other._mutex);
    if (other._firstElement != nullptr) {
        this->_firstElement = new ListElement<T>(*(other._firstElement));
    }
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList &other) {
    if (this != &other) {
        this->_DeleteAllElements();
        if(! other.Empty()){
            this->_firstElement = new ListElement<T>(*(other.Front()));
        }
    }
    return *this;
};

template <class T>
void LinkedList<T>::InsertAfter(ListElement<T>* insertAfterElement, T element){
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    ListElement<T>* newElement = new ListElement<T>(element);
    if (insertAfterElement->IsBeforeBegin()){
        if (_firstElement != nullptr){
            newElement->SetNext(_firstElement);
        }
        _firstElement = newElement;
    } else {
        ListElement<T>* oldNextElement = insertAfterElement->GetNext();
        insertAfterElement->SetNext(newElement);
        newElement->SetNext(oldNextElement);
    }
}

//TODO document that calling on empty list causes undefined behaviour
template <class T>
T LinkedList<T>::PopFront() {
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    if(_firstElement == nullptr) {
        throw InvalidPopUseException("Pop doesn't support being called on an empty list.");
    }
    T element = _firstElement->GetValue();
    ListElement<T>* newFirstElement = _firstElement->GetNext();

    delete _firstElement;
    _firstElement = newFirstElement;
    return element;
}

template <class T>
bool LinkedList<T>::Empty() {
    return _firstElement == nullptr;
}

template <class T>
ListElement<T>* LinkedList<T>::GetBeforeBegin() {
    return _beforeBegin;
}

template <class T>
ListElement<T> *LinkedList<T>::Front() {
    return _firstElement;
}

template <class T>
void LinkedList<T>::_DeleteAllElements(ListElement<T> *current) {
    if(current == nullptr) {
        if (_firstElement == nullptr) {
            return;
        } else {
            current = _firstElement;
            _firstElement = nullptr;
        }
    }
    if(current->GetNext() != nullptr) {
        _DeleteAllElements(current->GetNext());
    }
    delete current;
}

#endif //LINKED_LIST_H