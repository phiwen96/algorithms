#pragma once

#include "array_.hpp"
#include "pointee.hpp"





template <typename T, template <size_t...> typename Size, size_t N>
struct array <T, Size <N>>
{



private:
    pointee <T, Size <N>> m_p;
};






































#include "array_dynamic.hpp"


