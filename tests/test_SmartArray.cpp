#include "smartArray/SmartArray.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <sstream>

TEST(SmartArrayTest, DefaultConstructor) {
    SmartArray<int> arr;
    EXPECT_TRUE(arr.isEmpty());
    EXPECT_EQ(arr.size(), 0u);
    EXPECT_EQ(arr.capacity(), 100u);
}

TEST(SmartArrayTest, ConstructorWithSize) {
    SmartArray<int> arr(10);
    EXPECT_TRUE(arr.isEmpty());
    EXPECT_EQ(arr.capacity(), 100u);
}

TEST(SmartArrayTest, ConstructorWithSizeAndElement) {
    SmartArray<int> arr(5, 7);
    EXPECT_EQ(arr.size(), 5u);
    for (unsigned i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], 7);
    }
}

TEST(SmartArrayTest, PushBackAndAccess) {
    SmartArray<std::string> arr;
    arr.pushBack("hello");
    arr.pushBack("world");
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], "hello");
    EXPECT_EQ(arr[1], "world");
}

TEST(SmartArrayTest, AtWithException) {
    SmartArray<int> arr(2, 1);
    EXPECT_THROW(arr.at(5), std::out_of_range);
    EXPECT_NO_THROW(arr.at(1));
}

TEST(SmartArrayTest, ReserveAndCapacity) {
    SmartArray<int> arr;
    arr.reserve(100);
    EXPECT_GE(arr.capacity(), 100u);
}

TEST(SmartArrayTest, ResizeLarger) {
    SmartArray<int> arr(2, 1);
    arr.resize(4, 7);
    EXPECT_EQ(arr.size(), 4u);
    EXPECT_EQ(arr[2], 7);
    EXPECT_EQ(arr[3], 7);
}

TEST(SmartArrayTest, ResizeSmaller) {
    SmartArray<int> arr(5, 2);
    arr.resize(2);
    EXPECT_EQ(arr.size(), 2u);
}

TEST(SmartArrayTest, Clear) {
    SmartArray<int> arr(5, 9);
    arr.clear();
    EXPECT_TRUE(arr.isEmpty());
    EXPECT_EQ(arr.capacity(), 100u);
}

TEST(SmartArrayTest, InsertAndErase) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(3);
    arr.insert(1, 2);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr.size(), 3u);

    arr.erase(1);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr.size(), 2u);
}

TEST(SmartArrayTest, EraseRange) {
    SmartArray<int> arr(5, 1);
    arr.erase(1, 3);
    EXPECT_EQ(arr.size(), 2u);
}

TEST(SmartArrayTest, PopBack) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.popBack();
    EXPECT_EQ(arr.size(), 1u);
    EXPECT_EQ(arr[0], 1);
}

TEST(SmartArrayTest, EqualityOperator) {
    SmartArray<int> a(3, 5);
    SmartArray<int> b(3, 5);
    SmartArray<int> c(3, 6);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(SmartArrayTest, ShrinkToFit) {
    SmartArray<int> arr(10);
    arr.resize(3);
    arr.shrinkToFit();
    EXPECT_EQ(arr.capacity(), arr.size());
}

TEST(SmartArrayTest, PushPopFront) {
    SmartArray<int> arr;
    arr.pushBack(2);
    arr.pushFront(1);
    arr.pushBack(3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    arr.popFront();
    EXPECT_EQ(arr[0], 2);
}

TEST(SmartArrayTest, OutputToStream) {
    SmartArray<int> arr(3, 1);
    std::ostringstream oss;
    oss << arr;
    EXPECT_FALSE(oss.str().empty());  
}
