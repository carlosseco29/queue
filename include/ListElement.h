#ifndef QUEUE_ELEMENT_H
#define QUEUE_ELEMENT_H

#include "Exceptions.h"

template <class T>
class ListElement {
public:
    ListElement(T value) : value(value){};
    ListElement(const ListElement& other);
    ListElement& operator=(ListElement & other);
    bool IsBeforeBegin() const;
    void SetBeforeBegin();
    ListElement<T>* GetNext();
    void SetNext(ListElement<T>* next);
    const T GetValue();
    const ListElement<T>* GetNextConst() const;

private:
    const T value;
    ListElement<T>* next = nullptr;
};

template <class T>
ListElement<T>::ListElement(const ListElement &other)  : value(other.value) {
    if (other.IsBeforeBegin()) {
        this->SetBeforeBegin();
    } else if (other.GetNextConst() == nullptr) {
        this->next = nullptr;
    } else {
        this->next = new ListElement(*(other.GetNextConst()));
    }
    
}

template <class T>
ListElement<T> &ListElement<T>::operator=(ListElement<T> &other) {
    return ListElement(other);
}

template <class T>
bool ListElement<T>::IsBeforeBegin() const {
    return (this->next == this);
}

template <class T>
void ListElement<T>::SetBeforeBegin() {
    this->next = this;
}

template <class T>
ListElement<T>* ListElement<T>::GetNext() {
    if(this->IsBeforeBegin()) {
        throw InvalidBeforeBeginUseException("Calling GetNext on a BeforeBegin is unsupported");
    }
    return this->next;
}

template <class T>
const ListElement<T>* ListElement<T>::GetNextConst() const {
    if(this->IsBeforeBegin()) {
        throw InvalidBeforeBeginUseException("Calling GetNextConst on a BeforeBegin is unsupported");
    }
    return this->next;
}

template <class T>
void ListElement<T>::SetNext(ListElement<T> *next) {
    if(this->IsBeforeBegin()) {
        throw InvalidBeforeBeginUseException("Calling SetNext on a BeforeBegin is unsupported");
    }
    this->next = next;
}

template <class T>
const T ListElement<T>::GetValue() {
    if(this->IsBeforeBegin()) {
        throw InvalidBeforeBeginUseException("Calling GetValue on a BeforeBegin is unsupported");
    }
    return value;
}
#endif //QUEUE_ELEMENT_H