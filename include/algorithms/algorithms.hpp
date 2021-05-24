#pragma once
#include "common.hpp"
#include <ph_color/color.hpp>
using namespace std;

auto debug (auto const& A, auto const& low, auto const& mid, auto const& high)
{
    cout << low << " : " << mid << " : " << high << endl;
    cout << ph::color::white;
    
    for (int i = 0; i < low; ++i)
        cout << A [i] << " ";
    
    
    
    cout << ph::color::red << A [low] << " " << ph::color::white;
    
    for (auto i = A.begin () + low + 1; i < A.begin () + mid; ++i)
        cout << *i << " ";
    
    cout << ph::color::green << A [mid] << " " << ph::color::white;
    
    for (auto i = mid + 1; i < high - 1; ++i)
        cout << A [i] << " ";
    
    cout << ph::color::yellow << A [high] << " " << ph::color::white;
    
    for (auto i = high + 1; i < A.size (); ++i)
        cout << A [i] << " ";
    
    
    cout << endl;
}


/**
 @brief This algorithm returns true if it finds a specific key in an array, or false otherwise
 */
auto linear_search (auto const& cont, auto const& key) -> bool
{
    for (auto const& i : cont)
    {
        if (i == key)
        {
            return true;
        }
    }
    return false;
}


/**
 @brief  @brief This algorithm returns true if it finds a specific key in an array, or false otherwise
          The input container must be sorted.
 */
auto binary_search (auto const& A, auto const& key) -> bool
{
    auto low = 0;
    auto high = A.size ();
    
    while (low <= high)
    {
        auto mid = ph::mid (low, high);
        debug (A, low, mid, high);
       
        if (A [mid] > key)
        {
            high = mid - 1;
            
        } else if (A [mid] < key)
        {
            low = mid + 1;
            
        } else
        {
            return true;
        }
    }
    return false;
    /**
            9
         4   6   7   9  12
                    low = 0
                high = 5
                                    mid = 2
     */
}

