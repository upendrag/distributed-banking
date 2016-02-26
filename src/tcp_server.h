#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <netinet/in.h>

typedef struct sockaddr_in SocketAddr;

typedef void (*on_data_received) (void);

class TCP_Server
{
    public:
        TCP_Server(int portnum);
        void start(on_data_received odc);

    private:
        int parent_fd;
        int child_fd;
        int port_num;
        SocketAddr server_addr;
        
};

#endif
