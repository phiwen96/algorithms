#pragma once


#define MAXED_OUT (m_current == m_end)
#define GROW m_size *= growth_factor; grow();




template <typename T>
[[nodiscard]] inline auto allocate (size_t const number_of_elements, size_t align = alignof (T)) -> auto*
{
    return reinterpret_cast <T*> (::operator new (number_of_elements * sizeof (T), static_cast <std::align_val_t> (align)));
}


inline auto deallocate (auto* p, size_t align = alignof (decltype (p))) -> void
{
    ::operator delete (p, static_cast <std::align_val_t> (align));
}











template <typename T>
struct allocator : T
{
    using value_type = typename T::value_type;
    using pointer = typename T::pointer;
    using reference = typename T::reference;
    using dirrerence = typename T::difference;
    
    using T::m_begin;
    using T::m_end;
    using T::m_current;
    using T::capacity;
    using T::pushed;
    

    
    
    auto allocate (size_t n) -> pointer
    {
        return reinterpret_cast <pointer> (::operator new (sizeof (value_type) * n));
    }

    
    auto resize (auto&& n) -> auto&
    {
        if (n == capacity ()) return *this;
        if (n < 0) throw;
        
        auto activee = pushed ();
        
        m_begin = (pointer) aligned_alloc (alignof (value_type), sizeof (value_type) * std::forward <decltype (n)> (n));
        
        
        //    x x x x x 0 0 0
        //    x x x 0 0 0 0 0
        if (n <= activee)
        {
            m_current = m_begin + n;
            
        }
        
        //    x x x x 0 0 0 0
        //    x x x x x x 0 0
        else if (n > activee)
        {
            m_current = m_begin + activee;
        }
        
        m_end = m_begin + n;
        
        return *this;
    }
    
    template <typename U>
    auto operator= (U&& u) -> auto&
    requires requires (value_type& t, U&& u) {
        {t = std::forward <U> (u)};
    }
    {
        if (MAXED_OUT)
        {
            
        }
        return *this;
    }
    
};
