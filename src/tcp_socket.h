#ifndef TCP_SOCKET
#define TCP_SOCKET

#include "constants.h"
#include "exception.h"

#include <string>
#include <netinet/in.h>

#define MAX_FILE_NAME_LEN 128
#define MAX_WRITE_LEN 512
#define MAX_DATA_LEN 1024

// command input can be a string or integer
union CommandInput {
    char data[MAX_WRITE_LEN];
    int number;
};

// data struct carried by the socket buffer
struct SockData {
    CMD_TYPE cmd_t;
    char filename[MAX_FILE_NAME_LEN];
    CommandInput input;
};

class TcpSocket
{
    public:
        TcpSocket(std::string host, int port);
        ~TcpSocket() throw (Exception);
        void init(void) throw (Exception);
        void close(void) throw (Exception);
        void send(SockData* data) throw (Exception);
        std::string receive(void) throw (Exception);

    private:
        std::string host;
        int port;
        int sock_fd;
        struct hostent* host_entry;
        struct sockaddr_in host_addr;

        void connect(void) throw (Exception);
};

#endif
