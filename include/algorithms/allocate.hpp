#pragma once



template <typename T>
[[nodiscard]] inline auto allocate (size_t n) -> auto*
{
    return reinterpret_cast <T*> (::operator new (n * sizeof (T), static_cast <std::align_val_t> (alignof (T))));
}





