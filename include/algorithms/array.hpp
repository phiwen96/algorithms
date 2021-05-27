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







template <typename T>
struct array <T> : sequence <T>
{
    auto operator+= (auto&& e) -> auto&
    {
        ++m_p;
        m_p = forward <decltype (e)> (e);
        return *this;
    }

    operator size_t () const
    {
        return m_p.active ();
    }
    
    auto begin () -> auto
    {
        return m_p.m_begin;
    }
    
    auto end () -> auto
    {
        m_p.m_current;
    }
    
private:
    pointee <T> m_p;
    
};



