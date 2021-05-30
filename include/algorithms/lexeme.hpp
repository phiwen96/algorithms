#pragma once



struct lexeme
{
    char* begin;
    char* end;
    int line;
};


inline std::ostream& operator<< (std::ostream& os, lexeme const& l)
{
    return os << std::string (l.begin, l.end);
}
