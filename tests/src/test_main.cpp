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
#include <algorithms/operator.hpp>





template <typename T>
concept Int = std::is_same_v <T, int>;
template <typename T>
concept Char = std::is_same_v <T, char>;

//template <typename T>
//requires requires () {
//
//}


//template <template <typename> typename>
//concept boooo = true;

template <auto>
concept boooo = true;

template <auto>
concept boo =
    true;

//template <template <typename...> typename T, typename... U>
//concept noo = boo <T>;

template <typename A, typename B>
concept teeeee =
    not same_as <A, B>;


//template <typename b>
//requires requires (b&) {
//    requires (true);
//}

auto re ()
{
    return requires {1;};
}



template <typename>
concept Not = false;//requires (b&){requires (true);};

//template <Char i>
//concept Te = true;

template <typename...>
struct Test;

template <Int i>
struct Test <i> {
    
};



//template <typename T>
//struct Test <boo<Int<T>>>
//{
//
//};

template <typename T>
concept Float = true;//std::is_same_v <T, float>;
template <Not>
struct TTest
{
    
};
//template <typename T>
//requires (not Int <T>)
//struct Test <T>
//{
//
//};





template <typename T>
concept ja = true;


constexpr bool _ = requires ( int i) {
  ++i; // stop compilatopn if not satisfied
};


TEST_CASE ("new")
{
    using namespace std;
//    Test <char> t0;
    Test <int> t;
    
    Bajs b;
    for (auto a : b) {}
    
//    cout <<  Int <int>::value << endl;
}
















template <typename>
struct bajs;

template <>
struct bajs <int>
{
    
};

template <typename T>
concept Optional = requires {
  typename T::value_type;
  // ...
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
        
        {s.start}                          -> same_as <char*>;
        {s.current}                        -> same_as <char*>;
        {s.line}                           -> same_as <int>;

        {s.peek ()}                        -> same_as <char>;
        {s.peek_next ()}                   -> same_as <char>;
        {s.advance ()}                     -> same_as <char>;
        {s.is_at_end ()}                   -> same_as <bool>;
        {s.match (std::declval <char> ())} -> same_as <bool>;
        
        typename Token::lexeme_type;

        requires requires (Token& tok)
        {
            {tok.type} -> same_as <int>;
            {tok.lexeme} -> same_as <typename Token::lexeme_type>;
            {tok.line} -> same_as <int>;
        };
        
        
        
        requires requires (typename Token::lexeme_type& lex)
        {
            {lex.string}                          -> same_as <std::string_view>;
        };
    }
auto make_tokenizer () -> auto
{
    using Lexeme = typename Token::lexeme_type;
    
    return Tokenizer
    {
        [] <char c> (Scanner& sc) -> Token
        requires (c == '+')
        {
            
            return
            {
                .type = TOKEN_PLUS,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast<size_t>(sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '-')
        {
            
            
            return
            {
                .type = TOKEN_MINUS,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '*')
        {
            
            return
            {
                .type = TOKEN_STAR,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '\n' or c == ' ' or c == '\r' or c == '\t')
        {
            
            return
            {
                .type = TOKEN_WHITESPACE,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '/')
        {
            
            if (sc.match ('/'))
            {
                while (sc.peek () != '\n' and not sc.is_at_end ())
                {
                    sc.advance ();
                }
            }
            
            return
            {
                .type = TOKEN_SLASH,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '.')
        {
            
            return
            {
                .type = TOKEN_DOT,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == ',')
        {
            
            return
            {
                .type = TOKEN_COMMA,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == ':')
        {
            
            return
            {
                .type = TOKEN_COLON,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == ';')
        {
            
            return
            {
                .type = TOKEN_SEMICOLON,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '!')
        {
            
            return
            {
                .type = TOKEN_BANG,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '=')
        {
            
            
            return
            {
                .type = TOKEN_EQUAL,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '<')
        {
            
            return
            {
                .type = TOKEN_LESS,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '>')
        {
            
            return
            {
                .type = TOKEN_GREATER,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '(')
        {
            
            return
            {
                .type = TOKEN_LEFT_PAREN,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == ')')
        {
            
            return
            {
                .type = TOKEN_RIGHT_PAREN,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '{')
        {
            
            return
            {
                .type = TOKEN_LEFT_BRACE,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '}')
        {
            
            return
            {
                .type = TOKEN_RIGHT_BRACE,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '[')
        {
            
            return
            {
                .type = TOKEN_LEFT_BRACKET,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == ']')
        {
            
            return
            {
                .type = TOKEN_RIGHT_BRACKET,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c == '\0')
        {
            return
            {
                .type = TOKEN_EOF,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        requires (c >= '0' and c <= '9')
        {

            while (isdigit (sc.peek ()))
            {
                sc.advance();
            }
            
            if (sc.peek() == '.' and isdigit (sc.peek_next ()))
            {
                sc.advance();
                
                while (isdigit (sc.peek ()))
                {
                    sc.advance ();
                }
            }
            

            
            return
            {
                .type = TOKEN_NUMBER,
                
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        },
        
        [] <char c> (Scanner& sc) -> Token
        {
            
            if (sc.is_at_end ())
            {
                std::cout << "EEEEEND" << std::endl;
                return {};
            }
    
            std::cout << "WHAAAT" << std::endl;
            
            return
            {
                .lexeme = Lexeme
                {
                    .string = std::string_view {sc.start, static_cast <size_t> (sc.current - sc.start)},
                },
                
                .line = sc.line
            };
        }
    };
};








TEST_CASE("compiler")
{
    return;
    using namespace std;

    auto tokenizer = make_tokenizer <toki <lexeme>, scanner, overload> ();
    
    auto source = (char const*) "37.54//37\n+21-(7*4)";
    
    auto sc = scanner {source};
    
    
    
    auto token_generator = [] <typename... T> (overload <T...> & tokenizer, scanner& sc)
    {
        switch (sc.peek ())
        {
#define X(z, n, _) \
            case n: \
            {\
                sc.start = sc.current; \
                sc.advance(); \
                constexpr char q = n; \
                return tokenizer.template operator()<q>(sc); \
            }
                
                
                BOOST_PP_REPEAT (255, X, _)
#undef X
            default:
                break;
        }
    };
    
    for (auto tok = token_generator (tokenizer, sc);
         tok.type != TOKEN_EOF;
         tok = token_generator (tokenizer, sc))
    {
        cout << tok.lexeme << endl;
    }
    

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
