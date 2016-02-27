#include "utils.h"

#include <iterator>
#include <sstream>
#include <string.h>

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

void Utils::copy_str_to_arr(std::string str, char* arr,
    int len)
{
    if (!arr)
        throw Exception("Utils::copy_str_to_arr: undefined array");

    if (str.size() < (unsigned int)len)
        len = str.size();

    memset(arr, 0, len);
    memcpy(arr, str.c_str(), len);    
}

void Utils::reset_copy_arr(void* dest, void* src, int len)
{    
    if (!src || !dest)
        throw Exception("Utils::copy_str_to_arr: undefined array");

    memset(dest, 0, len);
    memcpy(dest, src, len);
}
