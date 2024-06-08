/// @file broker.hpp
/// @brief 

#include <map>
#include <queue>
#include <string>
#include <any>
#include <typeinfo>
#include <utility>

class MultiQueue
{
    public:

    template<typename T>
    void Push(T val)
    {
        data_[typeid(T).hash_code()].push(std::forward<T>(val));
    }

    template<typename T>
    T Pop()
    {
        auto it = data_.find(typeid(T).hash_code());

        if(it != data_.end())
        {
            if(!it->second.empty())
            {
                T res = std::any_cast<T>(it->second.front());
                it->second.pop();

                return res;
            }
        }

        throw "Empty queue";
    }

    private:

    std::map<size_t, std::queue<std::any>> data_;
};