#include <gtest/gtest.h>

#include "LinkedList.h"

/// @brief Tests the copy constructor 
TEST(LinkedListTest, Copy) {
    LinkedList<int> linkedList(0);
    LinkedList<int> linkedListCopy(linkedList);
    EXPECT_NE(linkedList.Begin(), linkedListCopy.Begin());
    EXPECT_EQ(linkedList.GetBeforeBegin(), linkedListCopy.GetBeforeBegin());
}

/// @brief Tests inserting at the end
TEST(LinkedListTest, InsertEnd) {
    LinkedList<int> linkedList(0);
    linkedList.InsertAfter(linkedList.Begin(), 1);
    EXPECT_EQ(linkedList.Begin()->GetNext()->GetValue(), 1);
}
/// @brief Tests inserting at the middle
TEST(LinkedListTest, InsertMiddle) {
    LinkedList<int> linkedList(0);
    linkedList.InsertAfter(linkedList.Begin(), 2);    
    linkedList.InsertAfter(linkedList.Begin(), 1);

    ListElement<int>* secondElement =  linkedList.Begin()->GetNext();
    ListElement<int>* thirdElement =  secondElement->GetNext();
    EXPECT_EQ(linkedList.Begin()->GetValue(), 0);
    EXPECT_EQ(secondElement->GetValue(), 1);
    EXPECT_EQ(thirdElement->GetValue(), 2);
}

/// @brief Tests tests inserting at the begining
TEST(LinkedListTest, InsertBegin) {
    LinkedList<int> linkedList(1);
    linkedList.InsertAfter(linkedList.GetBeforeBegin(), 0);

    ListElement<int>* secondElement =  linkedList.Begin()->GetNext();
    EXPECT_EQ(linkedList.Begin()->GetValue(), 0);
    EXPECT_EQ(secondElement->GetValue(), 1);
}

/// @brief Tests calling pop front on an empty list
TEST(LinkedListTest, PopFrontEmptyListThrowsException) {
    LinkedList<int> linkedList;
    EXPECT_THROW(linkedList.PopFront(), InvalidPopUseException);
}

/// @brief Tests calling pop front on a list with 1 element
TEST(LinkedListTest, PopFrontSingleElementList) {
    LinkedList<int> linkedList(0);
    EXPECT_EQ(linkedList.PopFront(), 0);
    EXPECT_EQ(linkedList.Begin(), nullptr);
}

/// @brief Tests calling pop front on a list with elements > 1
TEST(LinkedListTest, PopFrontMultiElementList) {
    LinkedList<int> linkedList(0);
    linkedList.InsertAfter(linkedList.Begin(), 1);
    EXPECT_EQ(linkedList.PopFront(), 0);
    EXPECT_EQ(linkedList.Begin()->GetValue(), 1);
}

/// @brief Tests the Empty method when the list is empty
TEST(LinkedListTest, EmptyEmptyList) {
    LinkedList<int> linkedList;
    EXPECT_EQ(linkedList.Empty(), true);
}

/// @brief Tests the Empty method when the list has values
TEST(LinkedListTest, EmptyNotEmptyList) {
    LinkedList<int> linkedList(0);
    EXPECT_EQ(linkedList.Empty(), false);

}

/// @brief Tests the Begin method when the list has values
TEST(LinkedListTest, Begin) {
    LinkedList<int> linkedList(1);
    linkedList.InsertAfter(linkedList.GetBeforeBegin(), 0);
    ASSERT_EQ(linkedList.Begin()->GetValue(), 0);
}
