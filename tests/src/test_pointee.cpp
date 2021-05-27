#ifdef RUN_CATCH

#include <catch2/catch.hpp>
#include <algorithms/pointee.hpp>



int a [10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

#define INIT(now) \
    auto p = pointee <int> {a, a + 10, now};


TEST_CASE ("active and passive")
{
    GIVEN ("a pointee")
    {
        auto p = pointee <int> {2};
        
        THEN ("passive == 2")
        {
            REQUIRE (p.passive() == 2);
        }
        
        THEN ("active == 0")
        {
            REQUIRE (p.active() == 0);
        }
    }
    GIVEN ("a pointee")
    {
        auto p = pointee <int> {nullptr, nullptr};
        
        THEN ("passive () == 0")
        {
            REQUIRE (p.passive() == 0);
        }
        
        THEN ("active () == 0")
        {
            REQUIRE (p.active() == 0);
        }
        
        AND_GIVEN ("end == begin + 2")
        {
            p.end = p.begin + 2;
            
            THEN ("passive () == 2")
            {
                REQUIRE (p.passive() == 2);
            }
        }
        
        AND_GIVEN ("now == begin + 1")
        {
            p.now = p.begin + 1;
            
            THEN ("active () == 1")
            {
                REQUIRE (p.active() == 1);
            }
        }
    }
}







#endif
