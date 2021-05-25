//#include "testlib.hpp"


#if defined (RUN_CATCH)

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>


auto main (int argc, char* argv[]) -> int
{
    int result = Catch::Session().run( argc, argv );
    return result;
}

#else

//#include <algorithms/sequence.hpp>
//#include <algorithms/allocator.hpp>
//#include <algorithms/timer.hpp>
//#include <algorithms/common.hpp>//#include "test.hpp"

cexp int loops = 10000000;

cexp int elements = 10;

auto main (int argc, char* argv[]) -> int
{
//    return run ();
//    timer t {"malloc no align"};
    
//    int* p = allocate <int> (elements, alignof (int));
//    int* p = reinterpret_cast <int*> (aligned_alloc (4, 8));
//    std::cout << sizeof (int) << std::endl << alignof (int) << std::endl;
//    *p = 10;
//    int* p = new int [elements];
//    for (int i = 0; i < 1; ++i)
//    {
////        p [i] = 10;
//    }
}


#endif

