#pragma once
#define INTERFACE(...)

template <typename...>
struct array;

INTERFACE ({
        
    struct array
    {
        auto operator[] (size_t i) -> array&;
    };
    
    
    
    {
        auto o = array <int> {};
        auto o = array <int, 10> {};
        auto o = array <int, 10, 10> {};
    }
    
})
