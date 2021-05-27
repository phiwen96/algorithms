#pragma once

#include "array_.hpp"
#include "common.hpp"

template <typename Pointee, template <typename...> typename Allocator>
concept is_ok = requires (Pointee& p) {
    typename Pointee::value_type;
    typename Pointee::reference;
    typename Pointee::pointer;
};

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
struct array <Allocator <Pointee>>
{
    cexp int growth_factor = 2;
    using pointee = Pointee;
    using allocator = Allocator <pointee>;
    using value_type = typename pointee::value_type;
    using reference = typename pointee::reference;
    using pointer = typename pointee::pointer;
    
    array (size_t passive = 2);
    
    auto push_back (value_type) -> auto&;
    auto passive () const -> size_t;
    auto active () const -> size_t;
    auto capacity () const -> size_t;
    auto begin ()   -> auto;
    auto end ()     -> auto;
    
    auto operator[] (size_t i) -> reference;
    auto operator[] (size_t i) const -> reference;

private:
    pointee p;
};



template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
array <Allocator <Pointee>>::array (size_t passive) : p {passive}
{
    allocator::allocate (p);
    p.now = p.begin;
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
auto array <Allocator <Pointee>>::push_back (value_type t) -> auto&
{
    if (FULL)
    {
        size_t act = active();
        p *= growth_factor;
        allocator::reallocate (p);
        p.now = p.begin + act;
    }
    
    *p.now = t;
    ++p.now;
    return *this;
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
auto array <Allocator <Pointee>>::passive () const -> size_t
{
    return p.passive ();
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
auto array <Allocator <Pointee>>::active () const -> size_t
{
    return p.active ();
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
auto array <Allocator <Pointee>>::capacity () const -> size_t
{
    return p.active () + p.passive ();
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
auto array <Allocator <Pointee>>::begin () -> auto
{
    return p.begin;
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
auto array <Allocator <Pointee>>::end () -> auto
{
    p.end;
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
auto array <Allocator <Pointee>>::operator[] (size_t i) -> reference
{
    assert (i >= 0 and i <= active());
    return * (p.begin + i);
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
auto array <Allocator <Pointee>>::operator[] (size_t i) const -> reference
{
    assert (i >= 0 and i <= active());
    return * (p.begin + i);
}

template <typename Pointee, template <typename...> typename Allocator>
requires (is_ok <Pointee, Allocator>)
inline std::ostream& operator<< (std::ostream& os, array<Allocator<Pointee>> const& a)
{
    for (int i = 0; i < a.active(); ++i)
    {
        os << a [i] << " ";
    }
    return os;
}


#include "array_1.hpp"
