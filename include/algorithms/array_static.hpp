#pragma once

#include "array_.hpp"
#include "pointee.hpp"





template <typename T>
requires requires (T& t)
{
    requires std::is_fundamental_v <T>;
}
struct array <T>
{



};






































#include "array_dynamic.hpp"


