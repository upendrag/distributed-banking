#include "exception.h"

Exception::Exception(std::string message) : message(message)
{}

std::string Exception::get_message(void)
{
    return this->message;
}
