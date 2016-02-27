#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "exception.h"
#include "tcp_socket.h"

class TcpServer
{
    public:
        TcpServer(int portnum) : main_socket(portnum)
        { }
        ~TcpServer() throw (Exception);
        void start(void) throw (Exception);
        
    private:
        TcpSocket main_socket;

};

#endif
