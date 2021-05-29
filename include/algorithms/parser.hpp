#pragma once
#include "token.hpp"

struct parser
{
    token current;
    token previous;
    bool had_error {false};
    bool panic_mode {false};
};
