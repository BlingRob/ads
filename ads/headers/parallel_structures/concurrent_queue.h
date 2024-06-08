/// @file concurrent_queue.h
/// @brief contains structures with parallel access

#pragma once
#ifndef __CONCURRENT_QUEUE_H__
#define __CONCURRENT_QUEUE_H__

#include <memory>
#include <mutex>
#include <atomic>
#include <stdexcept>

template <typename T>
class ConcurrentQueue
{
    struct Node
    {
        T t_;
        std::shared_ptr<Node> next_;
    };

    public:

    ConcurrentQueue() = default;
    ~ConcurrentQueue() = default;

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

    void Push(T t)
    {
        auto p = std::make_shared<Node>();

        p->t_ = t;
        p->next_ = nullptr;

        std::lock_guard<std::mutex> lk(mtx_);
        if(tail_ == head_ == nullptr)
        {
            tail_ = head_ = p;
        }
        else
        {
            tail_->next_ = p;
            tail_ = p;
        }

        size_.fetch_add(1);
    }

    /// @todo 
    void Pop()
    {

    }

    auto Front() const
    {
        if(!head_.load())
        {
            throw std::runtime_error{"Queue is empty"};
        }

        return Reference(head_);
    }

    auto Back() const
    {
        if(!tail_.load())
        {
            throw std::runtime_error{"Queue is empty"};
        }

        return Reference(tail_);
    }

    size_t Size() const
    {
        return size_.load();
    }

    private:

    std::shared_ptr<Node> head_;
    std::shared_ptr<Node> tail_;

    std::mutex mtx_;

    std::atomic<size_t> size_;
};

#endif // __CONCURRENT_QUEUE_H__