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
    OP_NEGATE,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE
};

struct token
{
    enum struct type
    {
        //single-character tokens
        TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
        TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
        TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
        TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,
        
        //one or two character tokens
        TOKEN_BANG, TOKEN_BANG_EQUAL,
        TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
        TOKEN_GREATER, TOKEN_GREATER_EQUAL,
        TOKEN_LESS, TOKEN_LESS_EQUAL,
        
        //literals
        TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,
        
        //keywords
        TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
        TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
        TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
        TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,
        
        TOKEN_ERROR, TOKEN_EOF
    };
    
    type t;
    char const* start;
    int length;
    int line;
};

struct scanner
{
    char const* start;
    char const* current;
    int line;
    
    scanner (char const* source) : start {source}, current {source}, line {1} {}
    
    auto scan_token () -> token
    {
        skip_whitespace ();
        
        start = current;
        
        if (is_at_end ())
        {
            return make_token (token::type::TOKEN_EOF);
        }
        
        char c = advance ();
        
        if (isdigit (c))
        {
            return number ();
        }
        
        
        switch (c)
        {
            case '(': return make_token (token::type::TOKEN_LEFT_PAREN);
            case ')': return make_token (token::type::TOKEN_RIGHT_PAREN);
            case '{': return make_token (token::type::TOKEN_LEFT_BRACE);
            case '}': return make_token (token::type::TOKEN_RIGHT_BRACE);
            case ';': return make_token (token::type::TOKEN_SEMICOLON);
            case ',': return make_token (token::type::TOKEN_COMMA);
            case '.': return make_token (token::type::TOKEN_DOT);
            case '-': return make_token (token::type::TOKEN_MINUS);
            case '+': return make_token (token::type::TOKEN_PLUS);
            case '/': return make_token (token::type::TOKEN_SLASH);
            case '*': return make_token (token::type::TOKEN_STAR);
                
            case '!': return make_token (match ('=') ? token::type::TOKEN_BANG_EQUAL : token::type::TOKEN_BANG);
            case '=': return make_token (match ('=') ? token::type::TOKEN_EQUAL_EQUAL : token::type::TOKEN_EQUAL);
            case '>': return make_token (match ('=') ? token::type::TOKEN_GREATER_EQUAL : token::type::TOKEN_GREATER);
            case '<': return make_token (match ('=') ? token::type::TOKEN_LESS_EQUAL : token::type::TOKEN_LESS);
                
            case '"': return string ();
        }
        
        
        
        return make_error_token ("Unexpected character.");
    }

    
private:
    auto number () -> token
    {
        while (isdigit (peek ()))
        {
            advance ();
        }
        
        if (peek () == '.' and isdigit (peek_next ()))
        {
            advance ();
            
            while (isdigit (peek ()))
            {
                advance ();
            }
        }
        
        return make_token (token::type::TOKEN_NUMBER);
    }
    
    auto string () -> token
    {
        while (peek () != '=' and !is_at_end ())
        {
            if (peek () == '\n')
            {
                ++line;
            }
            advance ();
        }
        
        if (is_at_end ())
        {
            return make_error_token ("Unterminated string.");
        }
        
        return make_token (token::type::TOKEN_STRING);
    }
    
    auto skip_whitespace () -> void
    {
        for (;;)
        {
            switch (char c = peek ()) {
                case '\n':
                    ++line;
                case ' ':
                case '\r':
                case '\t':
                {
                    advance ();
                    break;
                }
                case '/':
                {
                    if (peek_next () == '/')
                    {
                        // A comment goes until the end of the line.
                        while (peek () != '\n' and !is_at_end ())
                        {
                            advance ();
                        }
                    } else
                    {
                        return;
                    }
                }

                default:
                    return;
            }
        }
    }
    
    auto peek_next () const -> char
    {
        if (is_at_end ())
        {
            return '\0';
            
        } else
        {
            return current [1];
        }
    }
    
    auto peek () const -> char
    {
        return *current;
    }
    
    auto match (char expected) -> bool
    {
        if (is_at_end ())
        {
            return false;
            
        } else if (*current != expected)
        {
            return false;
        } else
        {
            ++current;
            return true;
        }
    }
    
    auto advance () -> char
    {
        return *(current--);
    }
    
    auto is_at_end () const -> bool
    {
        return *current == '\0';
    }
    
    auto make_token (token::type t) -> token
    {
        return
        {
            .t = t,
            .start = start,
            .length = (int) (current - start),
            .line = line
        };
    }
    
    auto make_error_token (char const* msg) -> token
    {
        return
        {
            .t = token::type::TOKEN_ERROR,
            .start = msg,
            .length = (int) strlen (msg),
            .line = line
        };
    }
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
                
            case opcode::OP_ADD:
                std::cout << "OP_ADD" << std::endl;
                break;
                
            case opcode::OP_SUBTRACT:
                std::cout << "OP_SUBTRACT" << std::endl;
                break;
                
            case opcode::OP_MULTIPLY:
                std::cout << "OP_MULTIPLY" << std::endl;
                break;
                
            case opcode::OP_DIVIDE:
                std::cout << "OP_DIVIDE" << std::endl;
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
                    int index = * (++ip);
                    int constant = consts [index];
                    push (constant);
                    ++ip;
                    break;
                }
                    
                case opcode::OP_NEGATE:
                {
                    push (-pop ());
                    ++ip;
                    break;
                }
                    
                case opcode::OP_ADD:
                {
                    push (pop () + pop ());
                    ++ip;
                    break;
                }
                    
                case opcode::OP_SUBTRACT:
                {
                    push (pop () - pop ());
                    ++ip;
                    break;
                }
                    
                case opcode::OP_MULTIPLY:
                {
                    push (pop () * pop ());
                    ++ip;
                    break;
                }
                    
                case opcode::OP_DIVIDE:
                {
                    push (pop () / pop ());
                    ++ip;
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
    
    [&]{
        code += opcode::OP_CONSTANT;
        consts += 10;
        code += consts.active() - 1;
        
        code += opcode::OP_CONSTANT;
        consts += 20;
        code += consts.active() - 1;
        code += opcode::OP_NEGATE;
        
        code += opcode::OP_CONSTANT;
        consts += 1;
        code += consts.active() - 1;
        
        code += opcode::OP_CONSTANT;
        consts += 2;
        code += consts.active() - 1;
        
        code += opcode::OP_ADD;
        
        code += opcode::OP_RETURN;
    }();
    
    
    
    
    
    
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


TEST_CASE ("")
{
    
}


#endif
