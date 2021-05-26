#pragma once




inline auto deallocate (auto* begin) -> void
{
    ::operator delete (begin, static_cast <std::align_val_t> (alignof (decltype (begin))));
}




