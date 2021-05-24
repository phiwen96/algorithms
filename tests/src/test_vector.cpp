//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/vector.hpp>



//using namespace std;




TEST_CASE ("test ph::vector")
{
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
