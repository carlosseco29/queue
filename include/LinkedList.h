#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <limits>

#include "Exceptions.h"
#include "ListElement.h"

/// @brief A templated class for a linked list
///
/// This class tries to mimic the std::forward_list's interface as much as possible
///
/// @tparam T The type of values that the linked list will hold
///
/// @note Only the methods needed for the operation of Queue.h have been implemented.
template <class T>
class LinkedList {
public:
    /// @brief The default constructor for the LinkedList
    ///
    /// This constructor initializes an empty LinkedList
    LinkedList() = default;
    
    /// @brief A constructor for the LinkedList
    ///
    /// This constructor initializes a list with the provided value
    ///
    /// @param value to initialize the first element of the list with
    LinkedList(const T value);

    /// @brief The copy constructor for the LinkedList
    ///
    /// This constructor creates a new LinkedList as a copy of the given one
    /// 
    /// @param other the LinkedList object to copy from
    LinkedList(const LinkedList& other);

    /// @brief The assignment operator for the LinkedList class
    ///
    /// This operator assigns the content of another LinkedList to the current object
    //
    /// @param other the LinkedList object to assign from
    ///
    /// @return A reference to the element LinkedList object after assignment.
    LinkedList& operator=(const LinkedList& other);

    /// @brief The destructor for the LinkedList
    ~LinkedList();
    
    /// @brief Inserts a new element in the queue after the provided one
    ///
    /// @param queueElement the queueElement to insert the value after
    /// @param value the value to insert after the queue element
    void InsertAfter(ListElement<T>* queueElement, T value);
    
    /// @brief Removes an item from the beginning of the list and returns its value
    ///
    /// @return the value of the item removed from the list
    /// @throws InvalidPopUseException if Pop is called on an empty list
    T PopFront();
    
    /// @brief A method which validates if the list is empty
    ///
    /// @return true if the list is empty, false otherwise
    bool Empty() const;
    
    /// @brief A method which returns the element representing the before the begin of the list
    ///
    /// This is represented by having the next pointer equal to the this pointer
    ///
    /// @return a pointer to a ListElement representing the element before the begin of the list
    ListElement<T>* GetBeforeBegin();
    
    /// @brief A method which returns the first element of the list
    ///
    /// @return a pointer to the first element of the list
    ListElement<T>* Begin();

    /// @brief A method which returns the first element of the list as const
    ///
    /// @return a const pointer to the first element of the list
    const ListElement<T>* BeginConst() const;

private:
    /// @brief The first element of the list
    ListElement<T>* _firstElement = nullptr;
    
    /// @brief The before begin of the list
    static ListElement<T>* _beforeBegin; 
    
    /// @brief A mutex to protect list operations
    mutable std::recursive_mutex _mutex;
    
    /// @brief A function which deletes all elements
    ///
    /// Deletes the element given to it and all its nexts
    /// use nullptr as a parameter to start from _firstElement
    ///
    /// @param element nullptr to start from _firstElement, element to start from otherwise
    void _DeleteAllElements(ListElement<T>* element = nullptr);
    
    /// @brief Creates a dinamically allocated BeforeBegin element
    ///
    /// @return a dinamically allocated BeforeBegin element, set to be freed on program exit
    static ListElement<T>* _CreateBeforeBegin();

    /// @brief Deletes the dinamically allocated BeforeBegin element
    static void _DeleteBeforeBegin();

    /// @brief A method which copies the values in other to the current object
    ///
    /// @param other the LinkedList object to copy from
    void _Copy(const LinkedList<T> &other);
};

#include "LinkedList.tpp"

#endif //LINKED_LIST_H