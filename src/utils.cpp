#include "utils.h"

#include <iterator>
#include <sstream>

int Utils::str_to_int(std::string val_str)
    throw (Exception)
{
    char first_char = val_str.at(0);
    // first character must be a digit or '-' or '+'
    if (val_str.empty() ||
        (!isdigit(first_char) &&
        first_char != '-' &&
        first_char != '+'))
        throw Exception("Not a number");
    
    char* str_end;
    int val = strtol(val_str.c_str(), &str_end, 10);
    // make sure the string is not of the type '3awd' or '324m'
    if (*str_end != 0)
        throw Exception("Not a number");
        
    return val;
}

std::vector<std::string> Utils::split_str(std::string str,
    std::string delim)
{
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    copy(std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(),
        back_inserter(tokens));
    return tokens;
}

