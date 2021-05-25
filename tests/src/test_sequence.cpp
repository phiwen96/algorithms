//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/sequence.hpp>
#include <algorithms/allocator.hpp>


//using namespace std;













TEST_CASE ("sequence")
{
    SECTION ("constructing")
    {
        sequence <int> s;
        REQUIRE (s.begin() == nullptr);
        REQUIRE (s.end() == nullptr);
        REQUIRE (s == nullptr);
    }
    
    SECTION ("capacity ()")
    {
        sequence <int> s;
        REQUIRE (s.capacity() == 0);
        
    }
    
    SECTION ("arithmetics")
    {
        sequence <int> s;
        
        REQUIRE (s.capacity() == 0);
        
    }
    sequence <int> s;
    REQUIRE (s.capacity() == 0);
    REQUIRE (s.pushed() == 0);
    
    s.begin() = (int*) aligned_alloc (alignof (int), sizeof (int) * 10);
    s.end() = s.begin() + 10;
    
    REQUIRE (s.capacity() == 10);
    
    s = s.begin();
    REQUIRE (s.pushed() == 0);
//    s +=
    s = s.begin () + 2;
    
    REQUIRE (s.pushed() == 2);
    s += 2;
    
    REQUIRE (s.pushed() == 4);
    
}

TEST_CASE("sequence + allo")
{
    allocator <sequence <int>> a;
    REQUIRE (a == nullptr);
    
    SECTION ("resize")
    {
        
    }
    a.resize (0);
    REQUIRE (a.capacity () == 0);
    REQUIRE (a.pushed () == 0);
    
    a.resize (2);
    REQUIRE (a.capacity () == 2);
    REQUIRE (a.pushed () == 0);
    
    a.resize (2);
    REQUIRE (a.capacity () == 2);
    REQUIRE (a.pushed () == 0);
    
    
    
}

#endif
