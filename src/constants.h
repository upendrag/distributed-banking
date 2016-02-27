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
const std::string ERR_INSUFF_ARGS = "Insufficient arguments for this option";

//enums
enum CMD_TYPE {
    E_CMD_NODE,
    E_CMD_CREATE,
    E_CMD_SEEK,
    E_CMD_READ,
    E_CMD_WRITE,
    E_CMD_DELETE,
    E_CMD_TERMINATE
};

#endif
