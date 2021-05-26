#pragma once

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
    
};



