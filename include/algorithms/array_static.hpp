#pragma once

#include "array_.hpp"
#include "pointee.hpp"





template <typename T, size_t N>
requires requires (T& t)
{
    requires std::is_fundamental_v <T>;
}
struct array <T, N>
{
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    
    array () = default;
    
    constexpr auto passive () const -> size_t
    {
        return p.passive ();
    }
    
    constexpr auto active () const -> size_t
    {
        return p.active ();
    }
    
    constexpr auto capacity () const -> size_t
    {
        return p.capacity ();
    }
    
    constexpr auto begin () -> pointer
    {
        return a;
    }
    
    constexpr auto end () -> pointer
    {
        return a + N;
    }

private:
    T a [N];
    pointee <T> p {a, a + N, a};
};






































#include "array_dynamic.hpp"


