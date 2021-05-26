#pragma once

template <size_t...>
struct size;

template <size_t n>
struct size <n>
{
    using type = size_t;
    inline static constexpr int value = n;
};
