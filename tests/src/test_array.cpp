#ifdef RUN_CATCH


#include <catch2/catch.hpp>
#include <algorithms/sequence.hpp>
#include <algorithms/allocator.hpp>
#include <algorithms/array.hpp>
#include <algorithms/size.hpp>


TEST_CASE ("interface")
{
    {
        auto o = array <int> {};
    }
}


TEST_CASE ("static array")
{
    
}

TEST_CASE ("dynamic array")
{
    GIVEN ("an allocator type")
    {
        using value_type = int;
        using allocator = allocator <pointee <int>>;
        
        AND_GIVEN ("an array with passive = 2")
        {
            constexpr auto capacity = size_t {2};
            auto a = array <allocator> {capacity};
            
            THEN ("passive == 2")
            {
                REQUIRE (a.passive() == 2);
            }
            
            THEN ("active == 0")
            {
                REQUIRE (a.active() == 0);
            }
            
            
            WHEN ("pushing")
            {
                GIVEN("a value")
                {
                    value_type value {10};
                    a.push_back (value);
                    
                    THEN ("active == 1")
                    {
                        REQUIRE (a.active() == 1);
                    }
                    
                    THEN ("passive == 1")
                    {
                        REQUIRE (a.passive() == 1);
                    }
                    
                    THEN ("element 0 == value")
                    {
                        REQUIRE (a [0] == value);
                    }
                    
                    AND_WHEN("pushing another value")
                    {
                        GIVEN ("another value")
                        {
                            value_type value2 {20};
                            a.push_back (value2);
                            
                            
                            
                            THEN ("active == 2")
                            {
                                REQUIRE (a.active() == 2);
                            }
                            
                            THEN ("passive == 2")
                            {
                                REQUIRE (a.active() == 2);
                            }
                            
                            THEN ("capacity has doubled")
                            {
                                REQUIRE (a.capacity() == capacity * 2);
                            }
                            
                            THEN ("element 1 == value2")
                            {
                                REQUIRE (a [1] == value2);
                            }
                            
                            THEN ("element 0 == value")
                            {
                                REQUIRE (a [0] == value);
                            }
                        }
                    }
                }
            }
        }
    }
}

#endif
