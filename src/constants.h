#ifndef CONSTANTS_H
#define CONSTANTS_H

#include<string>

// command strings
const std::string CMD_CREATE = "create";
const std::string CMD_SEEK = "seek";
const std::string CMD_READ = "read";
const std::string CMD_WRITE = "write";
const std::string CMD_DELETE = "delete";
const std::string CMD_TERMINATE = "terminate";
const std::string CMD_HELP = "help";

// reusable phrases
const std::string ERR_INSUFF_ARGS = "Insufficient arguments for the command";

#endif
