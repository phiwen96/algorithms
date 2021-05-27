#ifdef RUN_CATCH


#include <catch2/catch.hpp>
#include <algorithms/sequence.hpp>
#include <algorithms/allocator.hpp>
#include <algorithms/array.hpp>
#include <algorithms/size.hpp>




TEST_CASE ("static array")
{
    
}

TEST_CASE ("dynamic array")
{
    using pointee = pointee <int>;
    using allocator = allocator <pointee>;
    
    auto a = array <allocator> {};
    REQUIRE (a.size() == 0);
    a.push_back (5);
    REQUIRE (a.size() == 1);
    
}

#endif
