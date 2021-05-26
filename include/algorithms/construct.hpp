#pragma once



/**
 construct with values
 */
//auto construct (auto*, auto&&, auto&&...) -> void;
//
///**
// construct with no values
// */
//auto construct (auto*, auto*) -> void;
//
///**
// construct one with no value
// */
//auto construct (auto* p) -> void;


//template <typename... T>
//struct constr
//{
//    std::tuple <T...> m;
//
//    constr (T... t) : m {t...}
//    {
//
//    }
//};


auto construct (auto&&... t)
{
    return std::make_tuple (std::forward <decltype (t)> (t)...);
}

auto construct (auto&... t)
{
    return std::tie (t...);
}

template <template <typename...> typename T, typename... U>
auto operator| (auto* begin, T <U...>&& t)
{
    std::apply ([&begin](auto&&... a)
    {
        ((::new (begin++) std::decay_t <decltype (a)> {std::forward <decltype (a)> (a)}), ...);
    }, std::forward <T <U...>> (t));
}

//
//auto construct (auto* begin, auto&& first, auto&&... rest) -> auto*
//{
//    ::new (begin++) std::decay_t <decltype (first)> {std::forward <decltype (first)> (first)};
//
//
//    ((::new (begin++) std::decay_t <decltype (rest)> {std::forward <decltype (rest)> (rest)}), ...);
//
//    return begin;
//}
//
//
//auto construct (auto* begin, auto* end) -> auto*
//{
//    using type = std::remove_pointer_t <decltype (begin)>;
//
//    for (; begin < end; ++begin)
//    {
//        ::new (begin) type {};
//    }
//    return begin;
//}
//
//
//auto construct (auto* p) -> auto*
////requires (not std::is_trivially_default_constructible_v <std::remove_pointer_t <decltype (p)>>)
//{
//    using type = std::remove_pointer_t <decltype (p)>;
//    ::new (p) type {};
//    return p;
//}
//
//
