#ifndef UTILS_H
#define UTILS_H

#include "exception.h"

#include <cstdlib>
#include <iostream>
#include <string>

class Utils
{
    public:
        static void inline print_error(std::string msg)
        {
            std::cerr << "ERROR: " << msg << std::endl;
        }

        static int inline str_to_int(std::string val_str)
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
};
#endif
