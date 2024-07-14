#ifndef LIST_ELEMENT_H
#define LIST_ELEMENT_H

#include "Exceptions.h"

/// @brief A templated class for the elements of a linked list
///
/// Each list element holds its value and a pointer to the next element in the list
///
/// @tparam T The type of the value of the list element
template <class T>
class ListElement {
public:
    /// @brief The constructor for the ListElement
    ///
    /// This constructor initializes a ListElement with the given value
    ///
    /// @param value The value of the ListElement
    ListElement(T value) : _value(value){};

    /// @brief The copy constructor for the ListElement
    ///
    /// This constructor creates a new ListElement as a copy of the given one
    /// 
    /// @param other the ListElement object to copy from
    ///
    /// @note This constructor will copy _next recursively until it's null (end of list)
    ListElement(const ListElement& other);

    /// @brief The assignment operator for the ListElement class
    ///
    /// This operator assigns the content of another ListElement to the current oject
    /// @param other the ListElement object to assign from
    ///
    /// @return A reference to the current ListElement object after assignment.
    ///
    /// @note This constructor will copy _next recursively until it's null (end of list)
    ListElement& operator=(const ListElement & other);
    
    /// @brief Gets the value for the current element
    ///
    /// @return the value for the current element
    /// @throws InvalidBeforeBeginUseException if this method is called on before begin element
    const T GetValue();
    
    /// @brief Returns the pointer to the next element in the list
    ///
    /// @return the pointer to the next element in the list, nullptr if this Element is the last of the list
    /// @throws InvalidBeforeBeginUseException if this method is called on before begin element
    ListElement<T>* GetNext();

    /// @brief Gets a const pointer to the next element in the list
    /// @return a const pointer to the next element in the list, nullptr if this Element is the last of the list
    /// @throws InvalidBeforeBeginUseException if this method is called on before begin element
    const ListElement<T>* GetNextConst() const;
    
    /// @brief Sets the pointer to the next element in the list
    ///
    /// @param next the pointer to set as the next element in the list
    /// @throws InvalidBeforeBeginUseException if this method is called on before begin element
    void SetNext(ListElement<T>* next);
    
    /// @brief Checks if the current object representes the element before the begin of a list
    /// 
    /// @return true if current object representes the element before the begin of a list, false otherwise
    bool IsBeforeBegin() const;
    
    /// @brief Sets the current object as one that represents the one before the begin of a list
    void SetBeforeBegin();

private:
    /// @brief The value for the ListElement
    const T _value;

    /// @brief the pointer to the next element in the list
    ListElement<T>* _next = nullptr;

    /// @brief A method which copies the values in other to the current object
    ///
    /// @param other the ListElement object to copy from
    ///
    /// @note This method will copy _next recursively until it's nullptr (end of list)
    void _Copy(const ListElement<T> &other);
};

#include "../src/ListElement.tpp"

#endif //LIST_ELEMENT_H