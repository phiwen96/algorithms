//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/sequence.hpp>
#include <algorithms/allocator.hpp>
#include <algorithms/timer.hpp>
#include <algorithms/common.hpp>
#include <cstdlib>
#include <csetjmp>
#include <algorithms/construct.hpp>


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

struct A
{
    A()
    {
        std::cout << "A()\n";
    }
    A(A const&)
    {
        std::cout << "A(A const&)\n";
    }
    A(A&&)
    {
        std::cout << "A(A&&)\n";
    }
    ~A()
    {
        std::cout << "~A()\n";
    }
};




TEST_CASE("")
{
    A a;
    std::cout << "==========" << std::endl;
    auto* p = allocate <A> (3);
    construct (p, a);
    
    deallocate (p);
    std::cout << "==========" << std::endl;
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
