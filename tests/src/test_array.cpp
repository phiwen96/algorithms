//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/sequence.hpp>
#include <algorithms/allocator.hpp>
#include <algorithms/array.hpp>
#include <algorithms/size.hpp>


//using namespace std;













TEST_CASE ("static array")
{
    SECTION ("construction")
    {
        SECTION ("default")
        {
            auto a = array <int, size <10>> {};
        }
        
        SECTION ("value")
        {
            auto a = array <int, size <10>> {1, 2, 3};
        }
    }
}

TEST_CASE ("dynamic array")
{
    SECTION ("push back")
    {
        auto a = array <int> {};
        REQUIRE ((size_t) a == 0);
    }
}

#endif
