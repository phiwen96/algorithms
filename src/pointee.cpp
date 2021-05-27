#include "pointee.hpp"



template <typename T>
auto pointee <T>::operator++ () -> auto&
{
    ++now;
    return *this;
}

template <typename T>
auto pointee <T>::operator++ (int) -> auto&
{
    now++;
    return *this;
}

template <typename T>
auto pointee <T>::operator-- () -> auto&
{
    --now;
    return *this;
}

template <typename T>
auto pointee <T>::operator-- (int) -> auto&
{
    now--;
    return *this;
}

template <typename T>
auto pointee <T>::operator- (int i) -> auto&
{
    return *this;
}

template <typename T>
auto pointee <T>::operator+= (auto n) -> auto&
{
    now += n;
    return *this;
}

template <typename T>
auto pointee <T>::operator-= (auto n) -> auto&
{
    now -= n;
    return *this;
}

template <typename T>
auto pointee <T>::active () const -> size_t
{
    return end - begin;
}

template <typename T>
auto pointee <T>::passive () const -> size_t
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
