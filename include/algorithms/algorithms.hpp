#pragma once
#include "common.hpp"
using namespace std;



/**
 compare algorithms when the input size increases
 
 The algorithm with the slowest growth rate wins when the input size gets sufficiently large.
 
 */


/**
 @brief     O ( n )
            This algorithm returns true if it finds a specific key in an array, or false otherwise
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
 @brief O ( log n )
 
 
        This algorithm returns true if it finds a specific key in an array, or false otherwise
          The input container must be sorted.
 
 Lets say it contains 64 elements. In the first iteration, we reject 32 elements, in the next iteration we reject 16 elements and so on
until there are no more elements to compare of until we find the key.
 
 For an input size of 64, there will be, at most, 7 loop iterations. If we double the size to 128, we only need one more loop iteration.
 The growth rate is clearly not linear, its logarithic.
 */

auto binary_search (auto const& A, auto const& key) -> bool
{
    auto low = 0;
    auto high = A.size ();
    
    while (low <= high)
    {
        auto mid = ph::mid (low, high);
        
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

