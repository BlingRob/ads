#include <message_resender/multi_queue.hpp>

#include <gtest/gtest.h>

#include <thread>
#include <string>
#include <memory>

TEST(message_resender, simple_using)
{
    MultiQueue queue;

    const int testVal = 5;

    queue.Push(testVal);
    int retVal = queue.Pop<int>();

    ASSERT_EQ(testVal, retVal);
}

struct TestObject
{
    std::string name_;
};

TEST(message_resender, complex_object)
{
    MultiQueue queue;

    std::shared_ptr<TestObject> obj{std::make_shared<TestObject>()};

    queue.Push(obj);

    std::shared_ptr<TestObject> retVal = queue.Pop<std::shared_ptr<TestObject>>();

    ASSERT_NE(retVal, nullptr);
    ASSERT_EQ(retVal, obj);
}

TEST(message_resender, mix_return_values)
{
    MultiQueue queue;

    std::shared_ptr<TestObject> obj{std::make_shared<TestObject>()};
    const int testVal = 5;

    queue.Push(obj);
    queue.Push(testVal);

    std::shared_ptr<TestObject> retVal1 = queue.Pop<std::shared_ptr<TestObject>>();
    int retVal2 = queue.Pop<int>();


    ASSERT_EQ(retVal1, obj);
    ASSERT_EQ(retVal2, testVal);
}