#pragma once
#include "common.hpp"
#include <ph_color/color.hpp>
using namespace std;


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
        cout << red << "low: " << low << endl << "high: " << high << endl << "mid: " << mid << ":" << A [mid] << endl;
       
        cout << vector <int> (A.begin () + low, A.begin () + high) << endl;
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

