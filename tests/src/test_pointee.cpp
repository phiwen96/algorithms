//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/sequence.hpp>
#include <algorithms/allocator.hpp>
#include <algorithms/array.hpp>
#include <algorithms/size.hpp>


//using namespace std;










template <int a[6]>
struct A
{
    inline static int aa [10] {};
    cexp int * const begin {aa+1};
    cexp int * end {begin + 6};
};


TEST_CASE ("static array")
{
    SECTION ("construction")
    {
        SECTION ("default")
        {
            
            constexpr int * a {};
            constexpr auto a0 = A <a> {};
            constexpr int * i1 {a};
          
            
//            pp1 = i2;
            
            
            constexpr int aa[10] {};
//            constexpr int* ptr = std::decay_t <decltype (aa)> {aa};
//            constexpr auto s0 = sequence <int, size <10>> {aa, aa + 10};
            
            constexpr auto s1 = sequence <int> {};
//            p = 10;
        
//            std::cout << *p << std::endl;
//            auto a = array <int, size <10>> {};
        }
        
        SECTION ("value")
        {
//            auto a = array <int, size <10>> {1, 2, 3};
        }
    }
}

TEST_CASE ("dynamic array")
{
    SECTION ("push back")
    {
//        auto a = array <int> {};
//        REQUIRE ((size_t) a == 2);
    }
}

#endif
