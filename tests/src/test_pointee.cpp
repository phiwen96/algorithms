#ifdef RUN_CATCH

#include <catch2/catch.hpp>
#include <algorithms/pointee.hpp>



int a [10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

#define INIT(now) \
    auto p = pointee <int> {a, a + 10, now};


TEST_CASE ("dereference")
{
    INIT (a)
    
    REQUIRE (*p == 0);
}

TEST_CASE ("++")
{
    INIT (a)
    
    ++p;
    REQUIRE (*p.now == 1);
    REQUIRE (*p == 1);
    
    p++;
    REQUIRE (*p == 2);
}

TEST_CASE ("--")
{
    INIT (a + 2)
    
    --p;
    REQUIRE (*p == 1);
    
    p--;
    REQUIRE (*p == 0);
}

TEST_CASE ("+=")
{
    INIT (a)
    
    p += 2;
    REQUIRE (*p == 2);
}

TEST_CASE ("-=")
{
    INIT (a + 2)
    
    p -= 2;
    REQUIRE (*p == 0);
}


#endif
