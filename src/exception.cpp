#include "exception.h"

#include <errno.h>
#include <string.h>

Exception::Exception(std::string msg, bool useErrno) : message(msg)
{
    if (useErrno) {
        message.append(": ");
        message.append(strerror(errno));
    }
}

std::string Exception::get_message(void)
{
    return this->message;
}
