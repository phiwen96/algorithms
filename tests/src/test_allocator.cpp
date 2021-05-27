
#ifdef RUN_CATCH

#include <catch2/catch.hpp>


#include <algorithms/allocate.hpp>
#include <algorithms/pointee.hpp>





TEST_CASE ("")
{
    using allocator = allocator <pointee <int>>;
    
    auto p = pointee <int> {};
    ++p.end;
    allocator::allocate (p);
    p.now = p.begin;
    REQUIRE (p.active() == 0);
    
    
    
//    REQUIRE ()
}


#endif
