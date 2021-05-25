#pragma once




auto construct (auto* p, auto&& value) -> void
{
    ::new (p) std::decay_t <decltype (value)> {std::forward <decltype (value)> (value)};
}
