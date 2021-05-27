#pragma once
#include "sequence.hpp"
#include "allocator.hpp"

template <typename...>
struct pointee;




template <typename T>
struct pointee <T>// : sequence <T>, allocator <T>
{
#define EXPAND \
    auto i = m_i - m_begin; \
    m_end += i * 2; \
    allocator::reallocate (m_begin, m_end); \
    m_i = m_begin + i;
    
#define MAYBE_EXPAND \
    if (m_i >= m_end) {EXPAND}
    
//    using allocator = allocator <T>;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference = ptrdiff_t;
    
//    using sequence <T>::m_begin;
//    using sequence <T>::m_end;
//    using sequence <T>::m_current;
//    using sequence <T>::active;
//    using sequence <T>::passive;
//    sequence <T> m_seq;
//    pointer m_i;
    
    
    
//    pointee () //: m_i {m_begin + 1}
//    {
////        EXPAND
////        ++m_i;
//    }
    
    pointer begin;
    pointer end;
    pointer now;
    
    template <typename U>
    auto operator= (U && a) -> void
    requires requires (value_type& v) {
        {v = std::forward <U> (a)};
    }
    {
//        MAYBE_EXPAND
        
//        ::new (m_i) value_type {std::forward <U> (a)};
    }
    
    auto operator* () -> reference
    {
//        MAYBE_EXPAND
        
        return *now;
    }
    
//    auto operator&()
//    {
//        if (m_i >= m_end)
//        {
//            auto i = m_i - m_begin;
//            m_end += 1 + i * 2;
//            allocator::reallocate (m_begin, m_end);
//
//            m_i = m_begin + i;
//        }
//
//        return m_i;
//    }
    
    
    
    auto operator- (int i) -> auto&;
    auto operator+= (auto n) -> auto&;
    auto operator-= (auto n) -> auto&;
    auto operator++ () -> auto&;
    auto operator++ (int) -> auto&;
    auto operator-- () -> auto&;
    auto operator-- (int) -> auto&;
    auto active () const -> size_t;
    auto passive () const -> size_t;
    friend std::ostream& operator<< (std::ostream& os, pointee const& p);
};





template <typename T, template <size_t...> typename Size, size_t N>
struct pointee <T, Size <N>> : sequence <T, Size <N>>, allocator <T>
{
#define EXPAND \
    auto i = m_i - m_begin; \
    m_end += i * 2; \
    allocator::reallocate (m_begin, m_end); \
    m_i = m_begin + i;
    
#define MAYBE_EXPAND \
    if (m_i >= m_end) {EXPAND}
    
    
    using sequence = sequence <T, Size <N>>;
    using allocator = allocator <T>;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference = ptrdiff_t;
    
    using sequence::m_begin;
    using sequence::m_end;
    using sequence::m_current;
    using sequence::active;
    using sequence::passive;
    
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
    
    auto active () const -> size_t
    {
        return m_end - m_begin;
    }
    
    auto capacity () const -> size_t
    {
        return m_end - m_begin;
    }
    
    auto passive () const -> size_t
    {
        return m_end - m_current;
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



//auto operator() (auto&&... a) -> auto&
//{
//        MAYBE_EXPAND
//
//        auto curr = m_i - sizeof... (a);
//
//        ((::new (curr++) value_type {std::forward <decltype (a)>}), ...);
//        return *this;
//}
