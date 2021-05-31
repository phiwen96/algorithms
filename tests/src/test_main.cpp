#ifdef RUN_CATCH


#include <catch2/catch.hpp>
#include <algorithms/array.hpp>
#include <algorithms/common.hpp>
#include <algorithms/opcode.hpp>
#include <algorithms/vm.hpp>
#include <algorithms/compiler.hpp>
#include <algorithms/token.hpp>
#include <algorithms/lexeme.hpp>
#include <algorithms/scanner.hpp>















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










TEST_CASE ("interface")
{
    return;
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



//template <typename... tok>
//struct toka;

//template <typename

enum struct toki_type
{
#define X(x, ...) \
x,
    TOKEN
#undef X
};



template <typename Lexeme>
struct toki
{
    using lexeme_type = Lexeme;
//    type t;
    lexeme_type lex;
    int line {0};
};




#define TEST1(x) std::cout<<"TEST1: "<< x<<std::endl;


#define TEST(x) std::cout<<"TEST: "<< x<<std::endl; TEST1


template <typename... T>
struct overload : T...
{

    using T::operator()...;
    
    constexpr overload () = default;
    constexpr overload (T... t) : T {t}... {}
};





consteval int count_dots(std::string_view str) {
    return std::count_if(std::begin(str), std::end(str), [](auto s){return s == '.';});
}


template <typename Token, typename Scanner, template <typename...> typename Tokenizer>
    requires requires (Scanner& s) {
        {s.peek ()} -> same_as <char>;
        
        typename Token::lexeme_type;
        
        requires requires (typename Token::lexeme_type& lex) {
            {lex.begin} -> same_as <char*>;
            {lex.end} -> same_as <char*>;
            {lex.line} -> same_as <int>;
        };
    }
constexpr auto make_tokenizer () -> auto
{
    return Tokenizer
    {
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '+')
        {
            sc.advance ();
            
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '-')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '*')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '/')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '.')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == ',')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == ':')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == ';')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '!')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '=')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '<')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '>')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '(')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == ')')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '{')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '}')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == '[')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c == ']')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        requires (c >= '0' and c <= '9')
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        },
        
        [] <char c> (Scanner& sc) -> toki <lexeme>
        {
            return
            {
                .lex = lexeme
                {
                    sc
                },
            };
        }
    };
};




TEST_CASE("")
{
    using namespace std;

    auto tokenizer = make_tokenizer <toki <lexeme>, scanner, overload> ();
    
    auto source = (char const*) "37//37\n+2-(7*4)";
    
    auto sc = scanner {source};
    
    
    
    auto get_token = [] <typename... T> (overload <T...> & tokenizer, scanner& sc)
    {
        switch (sc.peek ())
        {
#define X(z, n, _) \
            case n: \
            {\
                constexpr char q = n; \
                return tokenizer.template operator()<q>(sc); \
            }
                
                
                BOOST_PP_REPEAT (255, X, _)
#undef X
            default:
                break;
        }
    };
    
    auto tok = get_token (tokenizer, sc);
    cout << *tok.lex.begin << endl;

}


TEST_CASE ("")
{
//    return;
    using namespace std;
    
//    auto source = (char const*) "37//37\n+2-(7*4)";
//
//    auto sc = scanner <token> {source};
//    token tok;
//
//    while (tok = (token) sc,
//           tok.t != token::type::TOKEN_EOF)
//    {
//        cout << tok.lex << endl;
//    }
    
    auto source = (char const*) "37//37\n+2-(7*4)";
    
//    auto sc = scanner <toki> {source};
//    toki<> tok = sc;
    
//    while (tok = (toki<>) sc,
//           tok.t != token::type::TOKEN_EOF)
//    {
//        cout << tok.lex << endl;
//    }
}

TEST_CASE ("")
{
    auto source = (char const*) "37//37\n+2-(7*4)";
    
//    auto c = compiler <scanner <token>> {source};
}

#endif
