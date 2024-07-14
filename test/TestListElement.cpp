#include <gtest/gtest.h>

#include "ListElement.h"

TEST(QueueElementTest, IsBeforeBegin) {
    ListElement<int> element(0);
    element.SetNext(&element);
    EXPECT_TRUE(element.IsBeforeBegin());
}

TEST(QueueElementTest, SetBeforeBegin) {
    ListElement<int> element(0);
    element.SetBeforeBegin();
    EXPECT_TRUE(element.IsBeforeBegin());
}

TEST(QueueElementTest, Copy) {
    ListElement<int> element(0);
    ListElement<int> element2(1);
    element.SetNext(&element2);
    ListElement<int> elementCopy(element);
    EXPECT_NE(element.GetNext(), elementCopy.GetNext());
    EXPECT_NE(&element, &elementCopy);
    EXPECT_EQ(element.GetValue(), elementCopy.GetValue());
    EXPECT_EQ(element.GetNext()->GetValue(), elementCopy.GetNext()->GetValue());
}

TEST(QueueElementTest, CopyNullNext) {
    ListElement<int> element(0);
    ListElement<int> elementCopy(element);
    EXPECT_EQ(element.GetNext(), nullptr);
    EXPECT_EQ(elementCopy.GetNext(), nullptr);
}

TEST(QueueElementTest, CopyBeforeBegin) {
    ListElement<int> element(0);
    element.SetBeforeBegin();
    ListElement<int> elementCopy(element);
    EXPECT_TRUE(elementCopy.IsBeforeBegin());
}
