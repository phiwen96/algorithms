#ifdef RUN_CATCH


#include <catch2/catch.hpp>
#include <algorithms/array.hpp>
#include <algorithms/common.hpp>

#define OPCODE \




enum struct opcode {
    OP_RETURN
};
std::ostream& operator<< (std::ostream& os, opcode const& o) {
    switch (o)
    {
        case opcode::OP_RETURN:
            return os << "OP_RETURN";
    }
    return os;
}


struct disassembler
{
    static auto disassemble (array <opcode> const& code)
    {
        for (auto i : code)
            std::cout << i << std::endl;
    }
};


TEST_CASE ("interface")
{
    auto o = array <opcode> {};
    o += opcode::OP_RETURN;
    
    disassembler::disassemble (o);
    std::cout << o.capacity() << std::endl;
}


#endif
