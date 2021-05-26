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


//using namespace std;



//timer t {"lol"};



cexp int loops = 10000000;

cexp int elements = 10;


template <typename T>
struct pointee : sequence <T>, allocator <T>
{
#define EXPAND \
    auto i = m_i - m_begin; \
    m_end += i * 2; \
    allocator::reallocate (m_begin, m_end); \
    m_i = m_begin + i;
    
#define MAYBE_EXPAND \
    if (m_i >= m_end) {EXPAND}
    
    using allocator = allocator <T>;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference = ptrdiff_t;
    
    using sequence <T>::m_begin;
    using sequence <T>::m_end;
    using sequence <T>::m_current;
    using sequence <T>::capacity;
    using sequence <T>::pushed;
    
    pointer m_i;
    
    pointee () : m_i {m_begin + 1}
    {
        EXPAND
    }
    
    template <typename U>
    auto operator= (U && a) -> void
    requires requires (value_type& v) {
        {v = std::forward <U> (a)};
    }
    {
        MAYBE_EXPAND
        
        ::new (m_i) value_type {std::forward <U> (a)};
    }
    
    auto operator* () -> reference
    {
        MAYBE_EXPAND
        
        return *m_i;
    }
    
    auto operator&()
    {
        if (m_i >= m_end)
        {
            auto i = m_i - m_begin;
            m_end += 1 + i * 2;
            allocator::reallocate (m_begin, m_end);
    
            m_i = m_begin + i;
        }
        
        return m_i;
    }
    
    auto operator-> () -> pointer
    {
        return m_current;
    }
    
    friend auto operator- (pointee& p, int i)
    {
        return pointee <T> {{p.m_begin, p.m_end, p.m_current - i}};
    }
    
    friend auto operator+= (pointee& p, size_t n) -> auto&
    {
        p.m_i += n;
        return p;
    }
    
    friend auto operator-= (pointee& p, size_t n) -> auto&
    {
        p.m_i -= n;
        return p;
    }
    
    auto operator() (auto&&... a) -> auto&
    {
        MAYBE_EXPAND
        
        auto curr = m_i - sizeof... (a);
        
        ((::new (curr++) value_type {std::forward <decltype (a)>}), ...);
        return *this;
    }
    
    
    
    auto operator++ () -> auto&
    {
        ++m_i;
        return *this;
    }
    auto operator++ (int) -> auto&
    {
        m_i++;
        return *this;
    }
    auto operator-- () -> auto&
    {
        --m_i;
        return *this;
    }
    auto operator-- (int) -> auto&
    {
        m_i--;
        return *this;
    }
    
    operator size_t () const
    {
        return m_end - m_begin;
    }
    
    friend std::ostream& operator<< (std::ostream& os, pointee const& p)
    {
        for (auto i = p.m_begin; i < p.m_end; ++i)
        {
            os << *i << " ";
        }
        return os;
    }
    
};

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
