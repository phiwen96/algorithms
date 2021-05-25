//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/vector.hpp>
#include <algorithms/timer.hpp>
#include <algorithms/common.hpp>





//using namespace std;





    

TEST_CASE ("test ph::vector")
{
    
    for (analyzer a {3}; a < 10; ++a)
    {
        std::cout << "tjo" << std::endl;
    }
    
    
    analyzer a {3};
    LOOP (10) ({int a;})
//    LOOP (3)
//    ({
//        std::cout << "hi" << std::endl;
//
//        LOOP (5)
//        ({
//            std::cout << "yoo" << std::endl;
//        })
//    })
    
    
    
    timer <true> t;
    vector <int> i;
//    std::cout << i.m_expensive_calls << std::endl;
    i += 3;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    i += 4;
    std::cout << i.m_pushed << std::endl;
    std::cout << i.m_pushed << std::endl;
//    std::cout <<
    
}










#endif
