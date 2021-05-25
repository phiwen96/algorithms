//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/sequence.hpp>
#include <algorithms/allocator.hpp>
#include <algorithms/timer.hpp>
#include <algorithms/common.hpp>



//using namespace std;



//timer t {"lol"};



cexp int loops = 10000000;

cexp int elements = 10;



//TEST_CASE ("::operator new no align")
//{
//#define SELF
//    {
//        timer t {"::operator new no align"};
//
//        LOOP (loops)
//        ({
////            allocate_align_1 <int> (40);
//
//        })
//    }
//#undef SELF
//}

TEST_CASE ("malloc no align")
{
    std::cout << sizeof (int) << std::endl;
    {
        timer t {"malloc no align"};
        
        LOOP (loops)
        ({
            auto* p = allocate <int> (elements, 8);

        })
    }
}
TEST_CASE ("malloc no align2")
{
    timer t {"malloc no align"};
    
    int* p = allocate <int> (elements);

    for (int i = 0; i < 3; ++i)
    {
        p [i] = 10;
    }
}






//TEST_CASE("sequence + allo")
//{
//    return;
//    allocator <sequence <int>> a;
//    REQUIRE (a == nullptr);
//
//    SECTION ("resize")
//    {
//
//    }
//    a.resize (0);
//    REQUIRE (a.capacity () == 0);
//    REQUIRE (a.pushed () == 0);
//
//    a.resize (2);
//    REQUIRE (a.capacity () == 2);
//    REQUIRE (a.pushed () == 0);
//
//    a.resize (2);
//    REQUIRE (a.capacity () == 2);
//    REQUIRE (a.pushed () == 0);
//
//    a = 5;
//
//
//
//}

#endif
