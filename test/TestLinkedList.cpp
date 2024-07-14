#include <gtest/gtest.h>

#include "LinkedList.h"

TEST(LinkedListTest, Copy) {
    LinkedList<int> linkedList(0);
    LinkedList<int> linkedListCopy = linkedList;
    EXPECT_NE(linkedList.Front(), linkedListCopy.Front());
    EXPECT_NE(linkedList.GetBeforeBegin(), linkedListCopy.GetBeforeBegin());
}

TEST(LinkedListTest, InsertBack) {
    LinkedList<int> linkedList(0);
    linkedList.InsertAfter(linkedList.Front(), 1);
    EXPECT_EQ(linkedList.Front()->GetNext()->GetValue(), 1);
}

TEST(LinkedListTest, InsertMiddle) {
    LinkedList<int> linkedList(0);
    linkedList.InsertAfter(linkedList.Front(), 2);    
    linkedList.InsertAfter(linkedList.Front(), 1);

    ListElement<int>* secondElement =  linkedList.Front()->GetNext();
    ListElement<int>* thirdElement =  secondElement->GetNext();
    EXPECT_EQ(linkedList.Front()->GetValue(), 0);
    EXPECT_EQ(secondElement->GetValue(), 1);
    EXPECT_EQ(thirdElement->GetValue(), 2);
}

TEST(LinkedListTest, InsertFront) {
    LinkedList<int> linkedList(1);
    linkedList.InsertAfter(linkedList.GetBeforeBegin(), 0);

    ListElement<int>* secondElement =  linkedList.Front()->GetNext();
    EXPECT_EQ(linkedList.Front()->GetValue(), 0);
    EXPECT_EQ(secondElement->GetValue(), 1);
}

TEST(LinkedListTest, PopFrontEmptyListThrowsException) {
    LinkedList<int> linkedList;
    EXPECT_THROW(linkedList.PopFront(), InvalidPopUseException);
}

TEST(LinkedListTest, PopFrontSingleElementList) {
    LinkedList<int> linkedList(0);
    EXPECT_EQ(linkedList.PopFront(), 0);
    EXPECT_EQ(linkedList.Front(), nullptr);
}

TEST(LinkedListTest, PopFrontMultiElementList) {
    LinkedList<int> linkedList(0);
    linkedList.InsertAfter(linkedList.Front(), 1);
    EXPECT_EQ(linkedList.PopFront(), 0);
    EXPECT_EQ(linkedList.Front()->GetValue(), 1);
}

TEST(LinkedListTest, EmptyEmptyList) {
    LinkedList<int> linkedList;
    EXPECT_EQ(linkedList.Empty(), true);
}

TEST(LinkedListTest, EmptyNotEmptyList) {
    LinkedList<int> linkedList(0);
    EXPECT_EQ(linkedList.Empty(), false);

}
TEST(LinkedListTest, Front) {
    LinkedList<int> linkedList(1);
    linkedList.InsertAfter(linkedList.GetBeforeBegin(), 0);
    ASSERT_EQ(linkedList.Front()->GetValue(), 0);
}
