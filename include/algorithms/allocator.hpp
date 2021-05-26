#pragma once


#define MAXED_OUT (m_current == m_end)
#define GROW m_size *= growth_factor; grow();


#include "allocate.hpp"

#include "deallocate.hpp"















template <typename T>
struct allocator
{
    using value_type = T;
    using pointer = value_type*;
    

    
    
    static auto allocate (pointer& begin, pointer& end)
    {
        auto size = end - begin;
        begin = reinterpret_cast <pointer> (std::malloc (sizeof (value_type) * (end - begin)));
        end = begin + size;
    }
    
    static auto deallocate (pointer& begin, pointer& end)
    {
        std::free (begin);
        begin = nullptr;
        end = nullptr;
    }
    
    static auto reallocate (pointer& begin, pointer& end)
    {
        auto size = end - begin;
        begin = reinterpret_cast <pointer> (std::realloc (begin, sizeof (value_type) * size));
        end = begin + size;
    }
    


    
};
