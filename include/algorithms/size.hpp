#pragma once



template <typename T>
struct size
{
//    using type = decltype (n);
    
//    inline static constexpr type value = n;
    T t;
    constexpr size (T t) : t {t} {}
};


//template <typename Size>
//size (Size n) -> size <n>;
