#ifndef UTILS_H
#define UTILS_H

#include "exception.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Utils
{
    public:
        static void inline print_error(std::string msg)
        {
            std::cerr << "ERROR: " << msg << std::endl;
        }
    
        static int str_to_int(std::string val_str) throw (Exception);

        std::vector<std::string> split_str(std::string str,
            std::string delim);
};
#endif
