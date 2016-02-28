#ifndef SOCK_DATA_CB_H
#define SOCK_DATA_CB_H

#include "tcp_socket.h"

typedef void (*on_sock_data)(SockData*, TcpSocket*);

class SockDataCb
{
    public:
        SockDataCb()
        { }
        ~SockDataCb()
        { }

        void subscribe(on_sock_data cb, SockData* data);

        void on_data_read(TcpSocket* sock) throw (Exception);

        SockData* sock_data;

    private:
        on_sock_data cb_func;
};

#endif
