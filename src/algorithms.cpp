#include "algorithms.hpp"
#include <ph_color/color.hpp>


auto debug (auto const& A, auto const& low, auto const& mid, auto const& high)
{
//    cout << low << " : " << mid << " : " << high << endl;
    std::cout << ph::color::white;
    
    for (int i = 0; i < low; ++i)
        cout << A [i] << " ";
    
    
    
    std::cout << ph::color::red << A [low] << " " << ph::color::white;
    
    for (auto i = A.begin () + low + 1; i < A.begin () + mid; ++i)
        cout << *i << " ";
    
    std::cout << ph::color::green << A [mid] << " " << ph::color::white;
    
    for (auto i = mid + 1; i < high - 1; ++i)
        cout << A [i] << " ";
    
    std::cout << ph::color::yellow << A [high-1] << " " << ph::color::white;
    
    for (auto i = high; i < A.size (); ++i)
        cout << A [i] << " ";
    
    
    cout << endl;
}
