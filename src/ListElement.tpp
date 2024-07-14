#include "ListElement.h"

template <class T>
ListElement<T>::ListElement(const ListElement &other)  : _value(other._value) {
    _Copy(other);
}

template <class T>
ListElement<T> &ListElement<T>::operator=(const ListElement<T> &other) {
    _Copy(other);
    return *this;
}

template <class T>
void ListElement<T>::_Copy(const ListElement<T> &other) {
    if (this != &other){
        if (other.IsBeforeBegin()) {
            this->SetBeforeBegin();
        } else if (other.GetNextConst() == nullptr) {
            this->_next = nullptr;
        } else {
            this->_next = new ListElement(*(other.GetNextConst()));
        }
    }
}

template <class T>
const T ListElement<T>::GetValue() {
    if(this->IsBeforeBegin()) {
        throw InvalidBeforeBeginUseException("Calling GetValue on a BeforeBegin is unsupported");
    }
    return _value;
}

template <class T>
ListElement<T>* ListElement<T>::GetNext() {
    if(this->IsBeforeBegin()) {
        throw InvalidBeforeBeginUseException("Calling GetNext on a BeforeBegin is unsupported");
    }
    return this->_next;
}

template <class T>
const ListElement<T>* ListElement<T>::GetNextConst() const {
    if(this->IsBeforeBegin()) {
        throw InvalidBeforeBeginUseException("Calling GetNextConst on a BeforeBegin is unsupported");
    }
    return this->_next;
}

template <class T>
void ListElement<T>::SetNext(ListElement<T> *next) {
    if(this->IsBeforeBegin()) {
        throw InvalidBeforeBeginUseException("Calling SetNext on a BeforeBegin is unsupported");
    }
    this->_next = next;
}

template <class T>
bool ListElement<T>::IsBeforeBegin() const {
    return (this->_next == this);
}

template <class T>
void ListElement<T>::SetBeforeBegin() {
    this->_next = this;
}