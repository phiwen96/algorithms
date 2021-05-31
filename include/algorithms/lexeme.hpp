#pragma once



struct lexeme
{
//    char* begin;
//    char* end;
    std::string_view string;

    
//    lexeme (auto& scanner) : begin {scanner.start}, end {scanner.current}, line {scanner.line}
//    {
//
//    }
};


inline std::ostream& operator<< (std::ostream& os, lexeme const& l)
{
    return os << "lexeme {\"" << l.string << "\"}";
}
