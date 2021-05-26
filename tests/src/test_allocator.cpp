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

#include <algorithms/allocate.hpp>
#include <algorithms/deallocate.hpp>

#include <algorithms/construct.hpp>
#include <algorithms/destruct.hpp>
#include <algorithms/pointee.hpp>


//using namespace std;



//timer t {"lol"};



cexp int loops = 10000000;

cexp int elements = 10;




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


TEST_CASE ("size")
{
    pointee <int> po;
    REQUIRE ((size_t) po == 2);
    po += 10;
    REQUIRE ((size_t) po == 2);
    po = 5;
    REQUIRE ((size_t) po == 24);
}

TEST_CASE("")
{
    
    pointee <int> po;
    std::cout << po << std::endl;
//    ++po;
    po = 20;
    --po;
    
    po += 20;
    
    
    
//    po = {3, 4, 5};
//    po = {1, 2, 3, 4};
    po += 10;
    
//    ++po;
//    std::cout << (po.m_i == po.m_begin) << std::endl;
//    std::cout << (size_t) po << std::endl;
//    ++po;
    *po = 10;
    
//    int& poo = *po;

    
//    *po = 20;
    
    
    
//    std::cout << (size_t) po << std::endl;
    
//    return 0;
//    po = 3;
    
    
    
//    std::cout << *(po - 1) << std::endl;
    
    
    
    
    
//    std::cout << *po << std::endl;
    
    return;
    int* pp {nullptr};
    int* pp2 = pp + 2;
    
    allocator<int>::allocate(pp, pp2);
    pp | construct (1, 2);
//    std::cout << *(pp++) << std::endl;
//    std::cout << *(pp++) << std::endl;
    std::cout << *(pp2-1) << std::endl;
    
    ++pp2;
    allocator<int>::reallocate (pp, pp2);
    pp | construct (1, 2, 3);
    std::cout << *(pp2-1) << std::endl;


    
//    std::cout << pp2-pp << std::endl;
    auto p = pointee <int> {};
    p = 4;
//    std::cout << *p << std::endl;
    
    []{
//        auto* pp = allocator <int>::allocate (3);
    //    construct (pp, 1, 2, 3);
        
//        pp | construct (1, 2, 3);
//
//
//        allocator <int>::reallocate (pp, 4);
//
//        destruct (pp, pp + 3);
//
//        allocator <int>::deallocate (pp);
    };
    

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
