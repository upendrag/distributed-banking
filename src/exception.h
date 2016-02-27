#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception
{
    public:
        Exception(std::string message, bool useErrno = false);
        std::string get_message(void);

    private:
        std::string message;
};

#endif
