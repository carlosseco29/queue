#include "LinkedList.h"

template<typename T>
ListElement<T>* LinkedList<T>::_beforeBegin = LinkedList::_CreateBeforeBegin();

template <class T>
ListElement<T>* LinkedList<T>::_CreateBeforeBegin() {
    ListElement<T>* beforeBegin = new ListElement<T>(T());
    beforeBegin->SetBeforeBegin();
    std::atexit(LinkedList::_DeleteBeforeBegin);
    return beforeBegin;
}

template <class T>
void LinkedList<T>::_DeleteBeforeBegin() {
    delete LinkedList::_beforeBegin;
}

template <class T>
LinkedList<T>::LinkedList(const T value) : LinkedList() {
    InsertAfter(_beforeBegin, value);
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList &other) : LinkedList()  {
    _Copy(other);
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &other) {
    if (this != &other) {
        if (! this->Empty()) {
            this->_DeleteAllElements();
        }
        _Copy(other);
    }
    return *this;
};

template <class T>
void LinkedList<T>::_Copy(const LinkedList<T> &other) {
    std::lock_guard<std::recursive_mutex> otherLockGuard(other._mutex);
    std::lock_guard<std::recursive_mutex> lockGuard(other._mutex);
    if (! other.Empty()) {
        this->_firstElement = new ListElement<T>(*(other._firstElement));
    }
}

template <class T>
LinkedList<T>::~LinkedList() {
    _DeleteAllElements();
}

template <class T>
void LinkedList<T>::_DeleteAllElements(ListElement<T> *element) {
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    if (Empty()) {
        return;
    } 
    if(element == nullptr) {
        element = _firstElement;
        _firstElement = nullptr;
    }
    if(element->GetNext() != nullptr) {
        _DeleteAllElements(element->GetNext());
    }
    delete element;
}

template <class T>
void LinkedList<T>::InsertAfter(ListElement<T>* insertAfterElement, T value){
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    ListElement<T>* newElement = new ListElement<T>(value);
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

template <class T>
T LinkedList<T>::PopFront() {
    std::lock_guard<std::recursive_mutex> lockGuard(_mutex);
    if(Empty()) {
        throw InvalidPopUseException("Pop doesn't support being called on an empty list.");
    }
    T value = _firstElement->GetValue();
    ListElement<T>* newFirstElement = _firstElement->GetNext();

    delete _firstElement;
    _firstElement = newFirstElement;
    return value;
}

template <class T>
bool LinkedList<T>::Empty()  const {
    return _firstElement == nullptr;
}

template <class T>
ListElement<T>* LinkedList<T>::GetBeforeBegin() {
    return _beforeBegin;
}

template <class T>
ListElement<T> *LinkedList<T>::Begin() {
    return _firstElement;
}

template <class T>
const ListElement<T> *LinkedList<T>::BeginConst() const {
    return _firstElement;
}