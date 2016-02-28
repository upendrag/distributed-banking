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
const std::string ERR_INSUFF_ARGS = "insufficient arguments for this option";

// info messages
const std::string INFO_FILE_CREATED = " -- success: file created";
const std::string INFO_FILE_DELETED = " -- success: file deleted";
const std::string INFO_FILE_SEEKED = " -- success: cursor position moved to ";
const std::string INFO_FILE_WRITTEN = " -- success: wrote text";

// error messages
const std::string FAIL_FILE_NOT_CREATED = " -- failure: cannot create file";
const std::string FAIL_FILE_EXISTS = " -- failure: file already exists";
const std::string FAIL_FILE_NOT_DELETED = " -- failure: cannot delete file";
const std::string FAIL_FILE_NOT_FOUND = " -- failure: file does not exist";
const std::string FAIL_SEEK_OOR = " -- failure: seek out of range";
const std::string FAIL_FILE_NOT_READABLE = " -- failure: file not readable";
const std::string FAIL_FILE_NOT_WRITABLE = " -- failure: file not writable";

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

//macros
#define CONCAT(x,y) x ## y

#endif
