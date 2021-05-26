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
    SECTION ("default constructor")
    {
        auto a = array <int, size <10>> {};
    }
    
    SECTION ("value constructor")
    {
        auto a = array <int, size <10>> {1, 2, 3};
    }
    
//    kuk<int, size<10>>::type
    
}

TEST_CASE ("dynamic array")
{
    auto a = array <int> {};
}

#endif
