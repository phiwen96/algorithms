#pragma once




auto destruct (auto* begin)
{
    using type = std::remove_pointer_t <decltype (begin)>;
    
    begin -> ~type ();
}

auto destruct (auto* begin, auto* end)
{
    using type = std::remove_pointer_t <decltype (begin)>;
    for (; begin < end; ++begin)
    {
        begin -> ~type ();
    }
}
