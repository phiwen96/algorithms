//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/algorithms.hpp>



using namespace std;

TEST_CASE ("test linear search")
{
    vector <int> i = {1, 3, 7, 9, 4};
    
    REQUIRE (linear_search (i, 7) == true);
    REQUIRE (linear_search (i, 8) == false);
}

TEST_CASE ("test binary search")
{
    vector <int> i = {1, 3, 7, 9, 16, 20};
    debug (i, 0/*1*/, ph::mid (i), 4/*16*/);
    debug (i, 1/*3*/, ph::mid (i), 4/*16*/);
//    REQUIRE (binary_search (i, 7) == true);
//    REQUIRE (binary_search (i, 8) == false);
}


#endif
