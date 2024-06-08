/// @file concurrent_stack.h
/// @brief mulitythread stack

#pragma once
#ifndef __CONCURRENT_STACK_H__
#define __CONCURRENT_STACK_H__

#include <memory>
#include <atomic>
#include <stdexcept>

/// From book Rainer Grimm
template <typename T>
class ConcurrentStack
{
    struct Node
    {
        T t_;
        std::shared_ptr<Node> next_;
    };

    public: 

    ConcurrentStack() = default;
    ~ConcurrentStack() = default;

    class Reference
    {
        public:

        Reference(std::shared_ptr<Node> p): p_{std::move(p)}
        {}

        T& operator* (){ return p_->t_; }
        T* operator-> (){ return &p_->t_; }

        private:

        std::shared_ptr<Node> p_;
    };

    auto Find(T t) const
    {
        auto p = head_.load();
        while(p && p->t_ != t)
        {
            p = p->next_;
        }

        if(!p)
        {
            throw std::runtime_error{"Value not found in stack"};
        }

        return Reference(std::move(p));
    }

    auto Top() const
    {
        if(!head_.load())
        {
            throw std::runtime_error{"Stack is empty"};
        }

        return Reference(head_);
    }

    void Push(T t)
    {
        auto p = std::make_shared<Node>();

        p->t_ = t;
        p->next_ = head_;

        while(!head_.compare_exchange_weak(p->next_, p)){}

        size_.fetch_add(1);
    }

    void Pop()
    {
        if(!head_.load())
        {
            throw std::runtime_error{"Stack is empty"};
        }

        auto p = head_.load();

        while(p && !head_.compare_exchange_weak(p, p->next_)){}

        size_.fetch_sub(1);
    }

    size_t Size() const
    {
        return size_.load();
    }

    private:

    ConcurrentStack(ConcurrentStack&) = delete;
    void operator=(ConcurrentStack&) = delete;

    private:

    std::atomic<std::shared_ptr<Node>> head_;
    std::atomic<size_t> size_;
};

#endif // __CONCURRENT_STACK_H__