#include <parallel_structures/concurrent_stack.h>

#include <gtest/gtest.h>

#include <thread>

TEST(parallel_structures, ConcurrentStack_sequence_empty_top)
{
    ConcurrentStack<int> stack;

    ///

    EXPECT_ANY_THROW(stack.Top());
}

TEST(parallel_structures, ConcurrentStack_sequence_top_1)
{
    ConcurrentStack<int> stack;

    ///
    stack.Push(1);

    ASSERT_EQ(*stack.Top(), 1);
}

TEST(parallel_structures, ConcurrentStack_sequence_top_2)
{
    ConcurrentStack<int> stack;

    ///
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    ASSERT_EQ(*stack.Top(), 3);
}

TEST(parallel_structures, ConcurrentStack_sequence_pop)
{
    ConcurrentStack<int> stack;

    ///
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    stack.Pop();

    ASSERT_EQ(*stack.Top(), 2);
}

TEST(parallel_structures, ConcurrentStack_sequence_find_yes)
{
    ConcurrentStack<int> stack;

    ///
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    ASSERT_EQ(*stack.Find(1), 1);
}

TEST(parallel_structures, ConcurrentStack_sequence_find_no)
{
    ConcurrentStack<int> stack;

    ///
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    EXPECT_ANY_THROW(stack.Find(4));
}

TEST(parallel_structures, ConcurrentStack_parallel_push)
{
    ConcurrentStack<int> stack;

    ///
    std::thread th1([&stack]
    {
        stack.Push(1);
    });

    std::thread th2([&stack]
    {
        stack.Push(2);
    });

    std::thread th3([&stack]
    {
        stack.Push(3);
    });

    th1.join();
    th2.join();
    th3.join();

    for(int i = 1; i < 4; ++i)
    {
        EXPECT_NO_THROW(stack.Find(i));
    }
}