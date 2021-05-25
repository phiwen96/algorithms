#pragma once

//using namespace std;



template <typename T>
struct sequence
{
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference = ptrdiff_t;
    
    sequence () noexcept : m_begin {nullptr}, m_end {nullptr}, m_current {nullptr}
    {
        
    }
    
    auto operator* () noexcept -> reference
    {
        return m_current;
    }
    
    auto capacity () const noexcept -> difference
    {
        return m_end - m_begin;
    }
    
    auto pushed () const noexcept-> difference
    {
        return m_current - m_begin;
    }
    
    auto begin () noexcept -> auto&
    {
        return m_begin;
    }
    
    auto end () noexcept -> auto&
    {
        return m_end;
    }
    
    auto operator= (auto&& other) noexcept
    {
        m_current = std::forward <decltype (other)> (other);
    }
    
    auto operator+= (auto&& i) noexcept
    {
        m_current += std::forward <decltype (i)> (i);
    }
    
    auto operator-= (auto&& i) noexcept
    {
        m_current -= std::forward <decltype (i)> (i);
    }
    
    auto operator*= (auto&& i) noexcept
    {
        m_current *= std::forward <decltype (i)> (i);
    }
    
    auto operator/= (auto&& i) noexcept
    {
        m_current /= std::forward <decltype (i)> (i);
    }
    
    auto operator--(auto&& i) noexcept -> sequence&
    {
        m_current -= std::forward <decltype (i)> (i);
    }
    
    friend auto operator== (sequence const& me, auto&& i) noexcept -> bool
    {
        return me.m_current == std::forward <decltype (i)> (i);
    }
    
    friend auto operator!= (sequence const& me, auto&& i) noexcept -> bool
    {
        return me.m_current != std::forward <decltype (i)> (i);
    }
    
    friend auto operator+ (sequence& me, auto&& i) noexcept -> pointer
    {
        return me.m_current + i;
    }
    
    friend auto operator- (sequence& me, auto&& i) noexcept -> pointer
    {
        return me.m_current - i;
    }
    
    operator bool () const noexcept
    {
        return m_current == nullptr or m_current == m_end;
    }
    
    
protected:
    pointer m_begin;
    pointer m_end;
    pointer m_current;
};
