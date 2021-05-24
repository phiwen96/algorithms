//#include "testlib.hpp"

#ifdef RUN_CATCH

//#include "test.hpp"
#include <catch2/catch.hpp>
#include <algorithms/sequence.hpp>



using namespace std;












template <typename T>
struct allo : T
{
    using value_type = typename T::value_type;
    using pointer = typename T::pointer;
    using reference = typename T::reference;
    using dirrerence = typename T::difference;
    
    using T::m_begin;
    using T::m_end;
    using T::m_current;
    using T::capacity;
    using T::active;
    

    

    
    auto resize (auto&& n) -> auto&
    {
        if (n == capacity ()) return *this;
        if (n < 0) throw;
        
        auto activee = active ();
        
        m_begin = (pointer) aligned_alloc (alignof (value_type), sizeof (value_type) * forward <decltype (n)> (n));
        
        
        //    x x x x x 0 0 0
        //    x x x 0 0 0 0 0
        if (n <= activee)
        {
            m_current = m_begin + n;
            
        }
        
        //    x x x x 0 0 0 0
        //    x x x x x x 0 0
        else if (n > activee)
        {
            m_current = m_begin + activee;
        }
        
        m_end = m_begin + n;
        
        return *this;
    }
};


TEST_CASE ("sequence")
{
    SECTION ("constructing")
    {
        sequence <int> s;
        REQUIRE (s.begin() == nullptr);
        REQUIRE (s.end() == nullptr);
        REQUIRE (s == nullptr);
    }
    
    SECTION ("capacity ()")
    {
        sequence <int> s;
        REQUIRE (s.capacity() == 0);
        
    }
    
    SECTION ("arithmetics")
    {
        sequence <int> s;
        
        REQUIRE (s.capacity() == 0);
        
    }
    sequence <int> s;
    REQUIRE (s.capacity() == 0);
    REQUIRE (s.active() == 0);
    
    s.begin() = (int*) aligned_alloc (alignof (int), sizeof (int) * 10);
    s.end() = s.begin() + 10;
    
    REQUIRE (s.capacity() == 10);
    
    s = s.begin();
    REQUIRE (s.active() == 0);
//    s +=
    s = s.begin () + 2;
    
    REQUIRE (s.active() == 2);
    s += 2;
    
    REQUIRE (s.active() == 4);
    
}

TEST_CASE("sequence + allo")
{
    allo <sequence <int>> a;
    REQUIRE (a == nullptr);
    
    SECTION ("resize")
    {
        
    }
    a.resize (0);
    REQUIRE (a.capacity () == 0);
    REQUIRE (a.active () == 0);
    
    a.resize (2);
    REQUIRE (a.capacity () == 2);
    REQUIRE (a.active () == 0);
    
    a.resize (2);
    REQUIRE (a.capacity () == 2);
    REQUIRE (a.active () == 0);
    
    
    
}

#endif
