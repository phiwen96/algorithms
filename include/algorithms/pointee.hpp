#pragma once
#include "sequence.hpp"
#include "allocator.hpp"

template <typename...>
struct pointee;




template <typename T>
struct pointee <T>
{
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference = ptrdiff_t;

    pointer begin {nullptr};
    pointer end {nullptr};
    pointer now {nullptr};
    
    auto active () const noexcept       -> size_t;
    auto passive () const noexcept      -> size_t;
    
    auto operator* () noexcept          -> reference;
    
    auto operator-  (int i) noexcept    -> auto&;
    auto operator+= (auto n) noexcept   -> auto&;
    auto operator-= (auto n) noexcept   -> auto&;
    auto operator++ () noexcept         -> auto&;
    auto operator++ (int) noexcept      -> auto&;
    auto operator-- () noexcept         -> auto&;
    auto operator-- (int) noexcept      -> auto&;
    
    friend std::ostream& operator<< (std::ostream& os, pointee const& p);
};














template <typename T>
auto pointee <T>::operator* () noexcept -> reference
{
    return *now;
}

template <typename T>
auto pointee <T>::operator++ () noexcept -> auto&
{
    ++now;
    return *this;
}

template <typename T>
auto pointee <T>::operator++ (int) noexcept -> auto&
{
    now++;
    return *this;
}

template <typename T>
auto pointee <T>::operator-- () noexcept -> auto&
{
    --now;
    return *this;
}

template <typename T>
auto pointee <T>::operator-- (int) noexcept -> auto&
{
    now--;
    return *this;
}

template <typename T>
auto pointee <T>::operator- (int i) noexcept -> auto&
{
    return *this;
}

template <typename T>
auto pointee <T>::operator+= (auto n) noexcept -> auto&
{
    now += n;
    return *this;
}

template <typename T>
auto pointee <T>::operator-= (auto n) noexcept -> auto&
{
    now -= n;
    return *this;
}

template <typename T>
auto pointee <T>::active () const noexcept -> size_t
{
    return now - begin;
}

template <typename T>
auto pointee <T>::passive () const noexcept -> size_t
{
    return end - now;
}


template <typename T>
inline std::ostream& operator<< (std::ostream& os, pointee <T> const& p)
{
    for (auto i = p.m_begin; i < p.m_end; ++i)
    {
        os << *i << " ";
    }
    return os;
}







//auto operator() (auto&&... a) -> auto&
//{
//        MAYBE_EXPAND
//
//        auto curr = m_i - sizeof... (a);
//
//        ((::new (curr++) value_type {std::forward <decltype (a)>}), ...);
//        return *this;
//}



//template <typename U>
//auto operator= (U && a) -> void
//requires requires (value_type& v) {
//    {v = std::forward <U> (a)};
//}
//{
//    MAYBE_EXPAND
//
//    ::new (m_i) value_type {std::forward <U> (a)};
//}


//#define EXPAND \
//    auto i = m_i - m_begin; \
//    m_end += i * 2; \
//    allocator::reallocate (m_begin, m_end); \
//    m_i = m_begin + i;
//
//#define MAYBE_EXPAND \
//    if (m_i >= m_end) {EXPAND}
