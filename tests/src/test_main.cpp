#ifdef RUN_CATCH


#include <catch2/catch.hpp>
#include <algorithms/array.hpp>
#include <algorithms/common.hpp>

#define OPCODE

using byte = int;


enum opcode : int
{
    OP_RETURN,
    OP_CONSTANT,
    OP_ADD,
    OP_NEGATE
};





template <auto...>
struct constant;

template <auto T>
requires requires ()
{
    requires (sizeof (T) == 1);
}
struct constant <T>
{
    using value_type = decltype (T);
    cexp value_type value = T;
    
};




auto disassemble = [] (array <int>& code, array <int>& consts) {
    
    auto dis_const = [&] (int*& i) {
        int index = * (i + 1);
        int c = consts [index];
        std::cout << "OP_CONSTANT " << c << std::endl;
        ++i;
    };
    
    for (auto i = code.begin(); i < code.end(); ++i)
    {
        switch (*i)
        {
            case opcode::OP_CONSTANT:
                dis_const (i);
                break;
                
            case opcode::OP_RETURN:
                std::cout << "OP_RETURN" << std::endl;
                break;
                
            case opcode::OP_NEGATE:
                std::cout << "OP_NEGATE" << std::endl;
                break;
                
            default:
                std::cout << "UNKNOWN" << std::endl;
                break;
        }
    }
};






struct vm
{
    cexp size_t stack_max = 256;
    enum result
    {
        OK,
        COMPILE_ERROR,
        RUNTIME_ERROR
    };
    int stack [stack_max];
    int* stack_top;
    int* ip;
    array <int>& code;
    array <int>& consts;
    
    vm (array <int>& code, array <int>& consts) : stack {}, stack_top {stack}, ip {code.begin()}, code {code}, consts {consts} {}
    auto run () -> result
    {
        while (ip < code.end())
        {
            switch (*ip)
            {
                case opcode::OP_RETURN:
                {
                    return result::OK;
                }
                case opcode::OP_CONSTANT:
                {
                    int index = *ip;
                    int constant = consts [* (ip + 1)];
                    push (constant);
                    ip += 2;
                    break;
                }
                case opcode::OP_NEGATE:
                {
                    push (-pop ());
                    break;
                }
                default:
                {
                    throw;
                }
                    
            }
        }
    }
    
private:
    auto push (int value) -> void
    {
        *stack_top = value;
        ++stack_top;
    }
    auto pop () -> int
    {
        return * (--stack_top);
    }
};



TEST_CASE ("interface")
{
    auto code   = array <int> {};
    auto consts = array <int> {};
    
    code += opcode::OP_CONSTANT;
    consts += 10;
    code += 0;
    
    code += opcode::OP_CONSTANT;
    consts += 20;
    code += 1;
    code += opcode::OP_NEGATE;
    
    
    code += opcode::OP_RETURN;
    
    
    
    
    auto v = vm {code, consts};
    
    
    
    
    disassemble (code, consts);
    
    std::cout << "==================" << std::endl;
    
    switch (vm::result r = v.run())
    {
        case vm::result::OK:
            break;
            
        case vm::result::COMPILE_ERROR:
            throw std::runtime_error ("compile error!");
            
        case vm::result::RUNTIME_ERROR:
            throw std::runtime_error ("runtime error!");
            
        default:
            break;
    }

}


#endif
