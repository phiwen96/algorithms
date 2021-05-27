
#ifdef RUN_CATCH

#include <catch2/catch.hpp>


#include <algorithms/allocate.hpp>
#include <algorithms/pointee.hpp>





TEST_CASE ("")
{
    GIVEN ("an allocator type")
    {
        using allocator = allocator <pointee <int>>;
        
        AND_GIVEN ("a pointee")
        {
            auto p = pointee <int> {};
            
            AND_GIVEN ("passive == 2")
            {
                p.end = p.begin + 2;
                
                WHEN ("allocating using this pointee")
                {
                    allocator::allocate (p);
                }
            }
        }
    }
}


#endif
