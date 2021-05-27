#pragma once
#include "pointee.hpp"
#include "sequence.hpp"


template <typename...>
struct array;


template <typename T, template <size_t...> typename Size, size_t N>
struct array <T, Size <N>>
{
    
    
  
private:
    pointee <T, Size <N>> m_p;
};







template <typename Pointee, template <typename...> typename Allocator>
struct array <Allocator <Pointee>>
{
    using pointee = Pointee;
    using allocator = Allocator <pointee>;
    using value_type = typename pointee::value_type;
    using reference = typename pointee::reference;
    using pointer = typename pointee::pointer;
    
    auto push_back (value_type) -> auto&;
    auto size () const -> size_t;
    auto begin ()   -> auto;
    auto end ()     -> auto;
    
    auto operator[] (size_t i) -> reference;

private:
    pointee p;
};





template <typename Pointee, template <typename...> typename Allocator>
auto array <Allocator <Pointee>>::push_back (value_type t) -> auto&
{
    ++p.end;
    allocator::allocate (p);
    *p = t;
    return *this;
}

template <typename Pointee, template <typename...> typename Allocator>
auto array <Allocator <Pointee>>::size () const -> size_t
{
    return p.now - p.begin;
}

template <typename Pointee, template <typename...> typename Allocator>
auto array <Allocator <Pointee>>::begin () -> auto
{
    return p.begin;
}

template <typename Pointee, template <typename...> typename Allocator>
auto array <Allocator <Pointee>>::end () -> auto
{
    p.end;
}

template <typename Pointee, template <typename...> typename Allocator>
auto array <Allocator <Pointee>>::operator[] (size_t i) -> reference
{
    return * (p.begin + i);
}



