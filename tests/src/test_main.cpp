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
    OP_ADD
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





struct chunk
{
    
    array <int> code;
    array <int> constants;
    
    auto add_opcode (int b) -> void
    {
        code += b;
    }
    
    auto add_constant (int c) -> int
    {
        constants += c;
        return constants.active() - 1;
    }

    

};



struct disassembler
{
    static auto disassemble_chunk (chunk const& c)
    {
        for (auto offset = c.code.begin(); offset < c.code.end(); ++offset)
        {
            offset = disassemble_instruction (c, offset);
        }

    }
    
    
private:
    static auto disassemble_instruction (chunk const& c, int* offset) -> int*
    {
        switch (*offset)
        {
            case opcode::OP_CONSTANT:
            {
                return constant_instruction ("OP_CONSTANT", c, offset);
            }
                
            case opcode::OP_RETURN:
            {
                return simple_instruction ("OP_RETURN", c, offset);
            }
                
            default:
            {
                throw;
            }
        }
    }
    static auto simple_instruction (char const* instr, chunk const& c, int* offset) -> int*
    {
        std::cout << instr << std::endl;
        return offset + 1;
    }
    static auto constant_instruction (char const* instr, chunk const& c, int* offset) -> int*
    {
        int constant = c.constants [* (offset + 1)];
        std::cout << instr << " " << constant << std::endl;
        return offset + 2;
    }
};





TEST_CASE ("interface")
{
    auto o = chunk {};
    o.add_opcode (opcode::OP_CONSTANT);
    o.add_opcode (o.add_constant (10));
    
    
    disassembler::disassemble_chunk (o);
}


#endif
