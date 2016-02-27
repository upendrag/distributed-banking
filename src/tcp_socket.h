#ifndef TCP_SOCKET
#define TCP_SOCKET

#include "constants.h"
#include "exception.h"

#include <string>
#include <netinet/in.h>

#define MAX_FILE_NAME_LEN 128
#define MAX_WRITE_LEN 512
#define MAX_DATA_LEN 1024
#define REQ_QUEUE_SZ 5

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
        TcpSocket() {}  //default constructor
        TcpSocket(int port, std::string host = "localhost");
        ~TcpSocket() throw (Exception);
        
        // socket API wrappers
        void connect(void) throw (Exception);
        void bind(void) throw (Exception);
        void listen(void) throw (Exception);
        void accept(TcpSocket& client_socket, 
            int& client_socket_len) throw (Exception);
        void send(void* data, int size) throw (Exception);
        void receive(void* data, int size) throw (Exception);
        void close(void) throw (Exception);

    private:
        std::string host;
        int port;
        int sock_fd;
        struct hostent* host_entry;
        struct sockaddr_in host_addr;

        void init(bool ifIpAddrAny = false) throw (Exception);
};

#endif
