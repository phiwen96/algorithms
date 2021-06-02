#include "operator.hpp"
#include "common.hpp"



struct TestOperator
{
    using precedence_type = int;
    cexp int precedence = 1;
    struct type
    {
        
    };
};


static_assert (requires {requires Operator <TestOperator>;}, "");



