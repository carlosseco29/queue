#ifndef QUEUE_ELEMENT_H
#define QUEUE_ELEMENT_H

template <class T>
class QueueElement {
public:
    QueueElement(T element) : element(element){};
    T element;
    QueueElement<T>* nextElement = nullptr;
};

#endif //QUEUE_ELEMENT_H