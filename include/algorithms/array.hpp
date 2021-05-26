#pragma once
#include "pointee.hpp"

template <typename...>
struct array;

struct sta; struct dyn;

template <typename T, template <size_t...> typename Size, size_t U>
struct array <T, Size <U>>
{
    using type = T;
    type m_begin [U];
};





template <typename T>
struct array <T>
{
    pointee <T> m_p;
    
    auto operator+= (auto&& e) -> auto&
    {
        ++m_p;
        m_p = forward <decltype (e)> (e);
        return *this;
    }

    operator size_t () const
    {
        return static_cast <size_t> (m_p);
    }
    
    auto begin () -> auto
    {
        return m_p.m_begin;
    }
    
    auto end () -> auto
    {
        m_p.m_current;
    }
};



