#pragma once
#define cexp(x) inline static constexpr x

#define MAXED_OUT (m_pushed == m_size)
#define GROW m_size *= growth_factor; grow();
#define PUSH ++m_pushed;

//#include <experimental/source_location>

template <typename T>
struct vector
{
    /**
     a big growth factor would potentially waste more memory but
     would make the expensive operation occur less frequently.
     */
    cexp (int) growth_factor = 2;
    cexp (int) start_size = 1;
    
    int m_size = start_size;
    int m_pushed = 0;
    
    auto operator+= (auto) -> void
    {
        if (MAXED_OUT)
        {
            GROW
        }
        
        PUSH
    }

    
    auto grow () -> void
    {
        std::cout << "GROWING" << std::endl;
    }
    
    
    
    
    
};








#undef cexp



//#ifdef MAXED_OUT
#undef MAXED_OUT
//#endif
