#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "exception.h"
#include "sock_data_cb.h"
#include "tcp_socket.h"

class TcpServer
{
    public:
        TcpServer(int portnum, SockDataCb* cb)
        : main_socket(portnum), client_data_cb(cb)
        { }
        ~TcpServer() throw (Exception);
        void start(void) throw (Exception);
        
    private:
        TcpSocket main_socket;
        SockDataCb* client_data_cb;
;
};

#endif
