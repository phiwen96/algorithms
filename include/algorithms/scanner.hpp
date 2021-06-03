#pragma once
//#include "token.hpp"


/*
 scanner doesn’t report lexical errors. Instead, it creates special error tokens and leaves it up to the parser to report them.
 */
BOOST_PP_EAT ({
    template <typename TokenType>
    struct scanner
    {
        using token_type = TokenType;
        
        char* start;
        char* current;
        int line;
        int const length;
        
        scanner (char const* source) : start {(char*) source}, current {(char*) source}, line {1}, length {strlen (source)}
        {
            
        }
        
        operator token_type ()
        {
            return typename token_type::make_token (start, current);
            skip_whitespace ();
            
            start = current;
            
            if (is_at_end ())
            {
                return make_token (token_type::type::TOKEN_EOF);
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
                case '(': return make_token (token_type::type::TOKEN_LEFT_PAREN);
                case ')': return make_token (token_type::type::TOKEN_RIGHT_PAREN);
                case '{': return make_token (token_type::type::TOKEN_LEFT_BRACE);
                case '}': return make_token (token_type::type::TOKEN_RIGHT_BRACE);
                case ';': return make_token (token_type::type::TOKEN_SEMICOLON);
                case ',': return make_token (token_type::type::TOKEN_COMMA);
                case '.': return make_token (token_type::type::TOKEN_DOT);
                case '-': return make_token (token_type::type::TOKEN_MINUS);
                case '+': return make_token (token_type::type::TOKEN_PLUS);
                case '/': return make_token (token_type::type::TOKEN_SLASH);
                case '*': return make_token (token_type::type::TOKEN_STAR);
                    
                case '!': return make_token (match ('=') ? token_type::type::TOKEN_BANG_EQUAL : token_type::type::TOKEN_BANG);
                case '=': return make_token (match ('=') ? token_type::type::TOKEN_EQUAL_EQUAL : token_type::type::TOKEN_EQUAL);
                case '>': return make_token (match ('=') ? token_type::type::TOKEN_GREATER_EQUAL : token_type::type::TOKEN_GREATER);
                case '<': return make_token (match ('=') ? token_type::type::TOKEN_LESS_EQUAL : token_type::type::TOKEN_LESS);
                    
                case '"': return string ();
            }
            
            
            
            return make_error_token ("Unexpected character.");
        }
        
        
    private:
        auto identifier_type () const -> typename token_type::type
        {
            switch (start [0]) {
                case 'a': return check_keyword (1, 2, "nd", token_type::type::TOKEN_AND);
                case 'c': return check_keyword (1, 4, "lass", token_type::type::TOKEN_CLASS);
                case 'e': return check_keyword (1, 3, "lse", token_type::type::TOKEN_ELSE);
                case 'f':
                    if (current - start > 1)
                    {
                        switch (start[1])
                        {
                            case 'a': return check_keyword(2, 3, "lse", token_type::type::TOKEN_FALSE);
                            case 'o': return check_keyword(2, 1, "r", token_type::type::TOKEN_FOR);
                            case 'u': return check_keyword(2, 1, "n", token_type::type::TOKEN_FUN);
                        }
                    }
                    break;
                case 'i': return check_keyword (1, 1, "f", token_type::type::TOKEN_IF);
                case 'n': return check_keyword (1, 2, "il", token_type::type::TOKEN_NIL);
                case 'o': return check_keyword (1, 1, "r", token_type::type::TOKEN_OR);
                case 'p': return check_keyword (1, 4, "rint", token_type::type::TOKEN_PRINT);
                case 'r': return check_keyword (1, 5, "eturn", token_type::type::TOKEN_RETURN);
                case 's': return check_keyword (1, 4, "uper", token_type::type::TOKEN_SUPER);
                case 't':
                    if (current - start > 1)
                    {
                        switch (start [1])
                        {
                            case 'h': return check_keyword (2, 2, "is", token_type::type::TOKEN_THIS);
                            case 'r': return check_keyword (2, 2, "ue", token_type::type::TOKEN_TRUE);
                        }
                    }
                    break;
                case 'v': return check_keyword (1, 2, "ar", token_type::type::TOKEN_VAR);
                case 'w': return check_keyword (1, 4, "hile", token_type::type::TOKEN_WHILE);
            }
            
            return token_type::type::TOKEN_IDENTIFIER;
        }
        
        auto check_keyword (int start, int length, const char* rest, typename token_type::type t) const -> typename token_type::type
        {
            if (this->current - this->start == start + length && memcmp (this->start + start, rest, length) == 0)
            {
                return t;
            }
            
            return token_type::type::TOKEN_IDENTIFIER;
        }
        
        auto is_alpha (char c) const -> bool
        {
            return (c >= 'a' and c <= 'z') or
            (c >= 'A' and c <= 'Z') or
            (c == '_');
        }
        
        auto identifier () -> token_type
        {
            while (is_alpha (peek ()) || isdigit (peek ()))
            {
                advance ();
            }
            
            return make_token (identifier_type ());
        }
        
        auto number () -> token_type
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
            return make_token (token_type::type::TOKEN_NUMBER);
        }
        
        auto string () -> token_type
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
            
            return make_token (token_type::type::TOKEN_STRING);
        }
        
        /// This advances the scanner past any leading whitespace. After this call returns, we know the very next character is a meaningful one (or we’re at the end of the source code).
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
        
        /// This simply returns the current character, but doesn’t consume it.
        auto peek () const -> char
        {
            return *current;
        }
        
        /// If the current character is the desired one, we advance and return true. Otherwise, we return false to indicate it wasn’t matched.
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
        
        /// consumes the current character and returns it.
        auto advance () -> char
        {
            return *(current++);
        }
        
        auto is_at_end () const -> bool
        {
            return *current == '\0';
        }
        
        auto make_token (typename token_type::type t) -> token_type
        {
    //        std::cout << *current << std::endl;
            return
            {
                .t = t,
                .lex
                {
                    .begin = start,
                    .end = current,
                    .line = line
                }
            };
        }
        
        auto make_error_token (char const* msg) -> token_type
        {
            return
            {
                .t = token_type::type::TOKEN_ERROR,
                .lex
                {
                    .begin = (char*) msg,
                    .end = (char*) msg + (int) strlen (msg),
                    .line = line
                }
            };
        }
    };
})


struct scanner
{
    char* start;
    char* current;
    int line;
    int const length;
    
    
    scanner (char const* source) : start {(char*) source}, current {(char*) source}, line {1}, length (strlen (source))
    {
        
    }
    
//    operator token_type <> ()
//    {
////        start = current;
//        char c = peek ();
//
//        if (c == '+')
//        {
//            return token_type <'+'>::create (*this);
//
//        } else if (c == '-')
//        {
//
//        } else if (c == '*')
//        {
//
//        } else if (c == '/')
//        {
//
//        } else if (c == '(')
//        {
//
//        } else if (c == ')')
//        {
//
//        } else if (c == '{')
//        {
//
//        } else if (c == '}')
//        {
//
//        } else if (c == '[')
//        {
//
//        } else if (c == ']')
//        {
//
//        }
//
//
////        return token_type <char c> (start, current);
////        skip_whitespace ();
//
////        start = current;
////
////        if (is_at_end ())
////        {
////            return make_token (token_type::type::TOKEN_EOF);
////        }
////
////        char c = advance ();
////
////        if (isdigit (c))
////        {
////            return number ();
////
////        } else if (is_alpha (c))
////        {
////            return identifier ();
////        }
//
////        switch (c)
////        {
////            case '(': return make_token (token_type::type::TOKEN_LEFT_PAREN);
////            case ')': return make_token (token_type::type::TOKEN_RIGHT_PAREN);
////            case '{': return make_token (token_type::type::TOKEN_LEFT_BRACE);
////            case '}': return make_token (token_type::type::TOKEN_RIGHT_BRACE);
////            case ';': return make_token (token_type::type::TOKEN_SEMICOLON);
////            case ',': return make_token (token_type::type::TOKEN_COMMA);
////            case '.': return make_token (token_type::type::TOKEN_DOT);
////            case '-': return make_token (token_type::type::TOKEN_MINUS);
////            case '+': return make_token (token_type::type::TOKEN_PLUS);
////            case '/': return make_token (token_type::type::TOKEN_SLASH);
////            case '*': return make_token (token_type::type::TOKEN_STAR);
////
////            case '!': return make_token (match ('=') ? token_type::type::TOKEN_BANG_EQUAL : token_type::type::TOKEN_BANG);
////            case '=': return make_token (match ('=') ? token_type::type::TOKEN_EQUAL_EQUAL : token_type::type::TOKEN_EQUAL);
////            case '>': return make_token (match ('=') ? token_type::type::TOKEN_GREATER_EQUAL : token_type::type::TOKEN_GREATER);
////            case '<': return make_token (match ('=') ? token_type::type::TOKEN_LESS_EQUAL : token_type::type::TOKEN_LESS);
////
////            case '"': return string ();
////        }
//
//
//
////        return make_error_token ("Unexpected character.");
//    }
    
    
//private:
//    auto identifier_type () const -> typename token_type::type
//    {
//        switch (start [0]) {
//            case 'a': return check_keyword (1, 2, "nd", token_type::type::TOKEN_AND);
//            case 'c': return check_keyword (1, 4, "lass", token_type::type::TOKEN_CLASS);
//            case 'e': return check_keyword (1, 3, "lse", token_type::type::TOKEN_ELSE);
//            case 'f':
//                if (current - start > 1)
//                {
//                    switch (start[1])
//                    {
//                        case 'a': return check_keyword(2, 3, "lse", token_type::type::TOKEN_FALSE);
//                        case 'o': return check_keyword(2, 1, "r", token_type::type::TOKEN_FOR);
//                        case 'u': return check_keyword(2, 1, "n", token_type::type::TOKEN_FUN);
//                    }
//                }
//                break;
//            case 'i': return check_keyword (1, 1, "f", token_type::type::TOKEN_IF);
//            case 'n': return check_keyword (1, 2, "il", token_type::type::TOKEN_NIL);
//            case 'o': return check_keyword (1, 1, "r", token_type::type::TOKEN_OR);
//            case 'p': return check_keyword (1, 4, "rint", token_type::type::TOKEN_PRINT);
//            case 'r': return check_keyword (1, 5, "eturn", token_type::type::TOKEN_RETURN);
//            case 's': return check_keyword (1, 4, "uper", token_type::type::TOKEN_SUPER);
//            case 't':
//                if (current - start > 1)
//                {
//                    switch (start [1])
//                    {
//                        case 'h': return check_keyword (2, 2, "is", token_type::type::TOKEN_THIS);
//                        case 'r': return check_keyword (2, 2, "ue", token_type::type::TOKEN_TRUE);
//                    }
//                }
//                break;
//            case 'v': return check_keyword (1, 2, "ar", token_type::type::TOKEN_VAR);
//            case 'w': return check_keyword (1, 4, "hile", token_type::type::TOKEN_WHILE);
//        }
//
//        return token_type::type::TOKEN_IDENTIFIER;
//    }
//
//    auto check_keyword (int start, int length, const char* rest, typename token_type::type t) const -> typename token_type::type
//    {
//        if (this->current - this->start == start + length && memcmp (this->start + start, rest, length) == 0)
//        {
//            return t;
//        }
//
//        return token_type::type::TOKEN_IDENTIFIER;
//    }
    
    auto is_alpha (char c) const -> bool
    {
        return (c >= 'a' and c <= 'z') or
        (c >= 'A' and c <= 'Z') or
        (c == '_');
    }
    
//    auto identifier () -> token_type
//    {
//        while (is_alpha (peek ()) || isdigit (peek ()))
//        {
//            advance ();
//        }
//
//        return make_token (identifier_type ());
//    }
    
//    auto number () -> token_type
//    {
//        while (isdigit (peek ()))
//        {
//            advance ();
//        }
//
//        if (peek () == '.' and isdigit (peek_next ()))
//        {
//            advance ();
//
//            while (isdigit (peek ()))
//            {
//                advance ();
//            }
//        }
//        return make_token (token_type::type::TOKEN_NUMBER);
//    }
//
//    auto string () -> token_type
//    {
//        while (peek () != '=' and !is_at_end ())
//        {
//            if (peek () == '\n')
//            {
//                ++line;
//            }
//            advance ();
//        }
//
//        if (is_at_end ())
//        {
//            return make_error_token ("Unterminated string.");
//        }
//
//        return make_token (token_type::type::TOKEN_STRING);
//    }
    
    /// This advances the scanner past any leading whitespace. After this call returns, we know the very next character is a meaningful one (or we’re at the end of the source code).
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
    
    /// This simply returns the current character, but doesn’t consume it.
    auto peek () const -> char
    {
        return *current;
    }
    
    /// If the current character is the desired one, we advance and return true. Otherwise, we return false to indicate it wasn’t matched.
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
    
    /// consumes the current character and returns it.
    auto advance () -> char
    {
        return *(current++);
    }
    
    auto is_at_end () const -> bool
    {
        return (current - start) >= length;
//        return *current == '\0';
    }
    
//    auto make_token (typename token_type::type t) -> token_type
//    {
////        std::cout << *current << std::endl;
//        return
//        {
//            .t = t,
//            .lex
//            {
//                .begin = start,
//                .end = current,
//                .line = line
//            }
//        };
//    }
    
//    auto make_error_token (char const* msg) -> token_type
//    {
//        return
//        {
//            .t = token_type::type::TOKEN_ERROR,
//            .lex
//            {
//                .begin = (char*) msg,
//                .end = (char*) msg + (int) strlen (msg),
//                .line = line
//            }
//        };
//    }
};
