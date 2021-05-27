#pragma once
#include "common.hpp"
//using namespace std;


/**
 sequence has three pointers
 */
template <typename...>
struct sequence;



template <typename T>
struct sequence <T>
{
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference = ptrdiff_t;
    
    constexpr sequence (pointer begin = nullptr, pointer end = nullptr, pointer current = nullptr) noexcept : m_begin {begin}, m_end {end}, m_current {current}
    {

    }
    constexpr auto active () const noexcept-> difference
    {
        return m_current - m_begin;
    }
    
    constexpr auto passive () const noexcept-> difference
    {
        return m_end - m_current;
    }
    
    
    
protected:
    pointer m_begin;
    pointer m_end;
    pointer m_current;
};

template <typename T, template <size_t...> typename Size, size_t N>
struct sequence <T, Size <N>>
{
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference = ptrdiff_t;
    
//    constexpr sequence (pointer begin, pointer end) noexcept //: m_begin {begin}, m_end {end}
//    {}
    
//    constexpr sequence () noexcept : m_values {}, m_begin {nullptr}, m_end {nullptr}, m_current {nullptr}//m_begin {m_values}, m_end {m_values + N}, m_current {m_values}
//    {
//
//    }
//    constexpr auto active () const noexcept-> difference
//    {
//        return m_current - m_begin;
//    }
//
//    constexpr auto passive () const noexcept-> difference
//    {
//        return m_end - m_current;
//    }

    
    
//private:
//    value_type m_values [N];
    
    
//protected:
    cexp pointer m_begin;// {m_values};
    T * const m_end;// {m_values + N};
//    pointer m_current;// {m_values};
};
