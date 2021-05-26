#pragma once
#include "sequence.hpp"
#include "allocator.hpp"

template <typename T>
struct pointee : sequence <T>, allocator <T>
{
#define EXPAND \
    auto i = m_i - m_begin; \
    m_end += i * 2; \
    allocator::reallocate (m_begin, m_end); \
    m_i = m_begin + i;
    
#define MAYBE_EXPAND \
    if (m_i >= m_end) {EXPAND}
    
    using allocator = allocator <T>;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference = ptrdiff_t;
    
    using sequence <T>::m_begin;
    using sequence <T>::m_end;
    using sequence <T>::m_current;
    using sequence <T>::capacity;
    using sequence <T>::pushed;
    
    pointer m_i;
    
    pointee () : m_i {m_begin + 1}
    {
        EXPAND
    }
    
    template <typename U>
    auto operator= (U && a) -> void
    requires requires (value_type& v) {
        {v = std::forward <U> (a)};
    }
    {
        MAYBE_EXPAND
        
        ::new (m_i) value_type {std::forward <U> (a)};
    }
    
    auto operator* () -> reference
    {
        MAYBE_EXPAND
        
        return *m_i;
    }
    
    auto operator&()
    {
        if (m_i >= m_end)
        {
            auto i = m_i - m_begin;
            m_end += 1 + i * 2;
            allocator::reallocate (m_begin, m_end);
    
            m_i = m_begin + i;
        }
        
        return m_i;
    }
    
    auto operator-> () -> pointer
    {
        return m_current;
    }
    
    friend auto operator- (pointee& p, int i)
    {
        return pointee <T> {{p.m_begin, p.m_end, p.m_current - i}};
    }
    
    friend auto operator+= (pointee& p, size_t n) -> auto&
    {
        p.m_i += n;
        return p;
    }
    
    friend auto operator-= (pointee& p, size_t n) -> auto&
    {
        p.m_i -= n;
        return p;
    }
    
    auto operator() (auto&&... a) -> auto&
    {
        MAYBE_EXPAND
        
        auto curr = m_i - sizeof... (a);
        
        ((::new (curr++) value_type {std::forward <decltype (a)>}), ...);
        return *this;
    }
    
    
    
    auto operator++ () -> auto&
    {
        ++m_i;
        return *this;
    }
    auto operator++ (int) -> auto&
    {
        m_i++;
        return *this;
    }
    auto operator-- () -> auto&
    {
        --m_i;
        return *this;
    }
    auto operator-- (int) -> auto&
    {
        m_i--;
        return *this;
    }
    
    operator size_t () const
    {
        return m_end - m_begin;
    }
    
    friend std::ostream& operator<< (std::ostream& os, pointee const& p)
    {
        for (auto i = p.m_begin; i < p.m_end; ++i)
        {
            os << *i << " ";
        }
        return os;
    }
    
};
