#pragma once

namespace ph{


constexpr auto mid (auto&& a, auto&& b) -> decltype (auto)
{
    return (a + b) / 2;
}

constexpr auto mid (auto&& a) -> decltype (auto)
{
    return a / 2;
}

constexpr auto mid (auto&& a) -> decltype (auto)
requires requires () {
    {a.size ()};
}
{
    return a.size () / 2;
}

static_assert (mid (2, 6) == 4, "");
static_assert (mid (6) == 3, "");


}



template <typename T>
std::ostream& operator<< (std::ostream& os, std::vector <T> const& v)
{
    for (auto const& i : v)
        os << i << " ";
    return os;
}
