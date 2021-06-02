#pragma once
#include "common.hpp"



template <typename T>
concept Operator = requires () {
    {T::precedence} -> convertible_to <int>;
//    T::precedence;
//    typename T::type;
};


