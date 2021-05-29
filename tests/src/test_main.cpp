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


/*
 scanner doesn’t report lexical errors. Instead, it creates special error tokens and leaves it up to the parser to report them.
 */
struct scanner
{
    char const* start;
    char const* current;
    int line;
    
    scanner (char const* source) : start {source}, current {source}, line {1}
    {
        
    }
    
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
            
        } else if (is_alpha (c))
        {
            return identifier ();
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
    auto identifier_type () const -> token::type
    {
        switch (start [0]) {
            case 'a': return check_keyword (1, 2, "nd", token::type::TOKEN_AND);
            case 'c': return check_keyword (1, 4, "lass", token::type::TOKEN_CLASS);
            case 'e': return check_keyword (1, 3, "lse", token::type::TOKEN_ELSE);
            case 'f':
                if (current - start > 1)
                {
                    switch (start[1])
                    {
                        case 'a': return check_keyword(2, 3, "lse", token::type::TOKEN_FALSE);
                        case 'o': return check_keyword(2, 1, "r", token::type::TOKEN_FOR);
                        case 'u': return check_keyword(2, 1, "n", token::type::TOKEN_FUN);
                    }
                }
                break;
            case 'i': return check_keyword (1, 1, "f", token::type::TOKEN_IF);
            case 'n': return check_keyword (1, 2, "il", token::type::TOKEN_NIL);
            case 'o': return check_keyword (1, 1, "r", token::type::TOKEN_OR);
            case 'p': return check_keyword (1, 4, "rint", token::type::TOKEN_PRINT);
            case 'r': return check_keyword (1, 5, "eturn", token::type::TOKEN_RETURN);
            case 's': return check_keyword (1, 4, "uper", token::type::TOKEN_SUPER);
            case 't':
                if (current - start > 1)
                {
                    switch (start [1])
                    {
                        case 'h': return check_keyword (2, 2, "is", token::type::TOKEN_THIS);
                        case 'r': return check_keyword (2, 2, "ue", token::type::TOKEN_TRUE);
                    }
                }
                break;
            case 'v': return check_keyword (1, 2, "ar", token::type::TOKEN_VAR);
            case 'w': return check_keyword (1, 4, "hile", token::type::TOKEN_WHILE);
        }
        
        return token::type::TOKEN_IDENTIFIER;
    }
    
    auto check_keyword (int start, int length, const char* rest, token::type t) const -> token::type
    {
        if (this->current - this->start == start + length && memcmp (this->start + start, rest, length) == 0)
        {
            return t;
        }
        
        return token::type::TOKEN_IDENTIFIER;
    }
    
    auto is_alpha (char c) const -> bool
    {
        return (c >= 'a' and c <= 'z') or
        (c >= 'A' and c <= 'Z') or
        (c == '_');
    }
    
    auto identifier () -> token
    {
        while (is_alpha (peek ()) || isdigit (peek ()))
        {
            advance ();
        }
        
        return make_token (identifier_type ());
    }
    
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

struct parser
{
    token current;
    token previous;
    bool had_error {false};
    bool panic_mode {false};
};

/**
 The compiler will take the user’s program and fill up the chunk with bytecode.
 At least, that’s what it will do if the program doesn’t have any compile errors.
 
 A compiler has roughly two jobs. It parses the user’s source code to understand what it means. Then it takes that knowledge and outputs low-level instructions that produce the same semantics.
 */
struct compiler
{
    array <int> code;
    array <int> consts;
    scanner sc;
    parser prs;
    
    compiler (char const* source) : sc {source}
    {
        advance ();
        expression ();
        consume (token::type::TOKEN_EOF, "Expect end of expression.");
    }
    
    // returns whether or not compilation succeeded
    operator bool () const
    {
        return not prs.had_error;
    }
    
private:
    auto unary() -> void
    {
      token::type operatorType = prs.previous.t;

      // Compile the operand.
      expression ();

      // Emit the operator instruction.
      switch (operatorType)
      {
          case token::type::TOKEN_MINUS: emit_bytes (opcode::OP_NEGATE); break;
          default: return; // Unreachable.
      }
    }
    
    auto grouping() -> void
    {
      expression ();
      consume (token::type::TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
    }
    
    auto number() -> void
    {
      int value = strtod (prs.previous.start, NULL);
      emit_constants (value);
    }
    
    auto emit_constants(int value) -> void
    {
      emit_bytes (opcode::OP_CONSTANT, make_constant (value));
    }
    
    auto make_constant (int value) -> int
    {
        consts += value;
        int index = consts.active ();
        
//      if (constant > UINT8_MAX) {
//        error("Too many constants in one chunk.");
//        return 0;
//      }

      return index;
    }
    
    auto expression () -> void
    {
        
    }
    
    auto emit_return (int b) -> void
    {
        emit_bytes (opcode::OP_RETURN);
    }
    
    auto emit_bytes (auto... b) -> void
    {
        ((code += b), ...);
    }
    
    /*
     It asks the scanner for the next token and stores it for later use.
     Before doing that, it takes the old current token and stashes that in a previous field.
     */
    auto advance () -> void
    {
        prs.previous = prs.current;
        
        prs.current = sc.scan_token ();
        
        if (prs.current.t == token::type::TOKEN_ERROR)
        {
            throw;
        }
    }
    
    auto consume (token::type t, const char* msg) -> void
    {
      if (prs.current.t == t)
      {
        advance ();
        return;
      }

      error_at_current (msg);
    }
    
    auto error_at_current(const char* msg) -> void
    {
        error_at (&prs.current, msg);
    }
    
    auto error(const char* msg) -> void
    {
        error_at (&prs.previous, msg);
    }
    
    auto error_at (token* tok, const char* msg) -> void
    {
        if (prs.panic_mode)
        {
            return;
        }
        
        prs.panic_mode = true;
        
        fprintf (stderr, "[line %d] Error", tok->line);
        
        if (tok->t == token::type::TOKEN_EOF)
        {
            fprintf(stderr, " at end");
            
        } else if (tok->t == token::type::TOKEN_ERROR)
        {
            // Nothing.
        } else
        {
            fprintf(stderr, " at '%.*s'", tok->length, tok->start);
        }
        
        fprintf (stderr, ": %s\n", msg);
        prs.had_error = true;
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
    auto code   = array <int> {};
    auto consts = array <int> {};
    
    auto v = vm {code, consts};
}


#endif
