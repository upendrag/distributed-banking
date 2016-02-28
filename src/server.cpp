#include "constants.h"
#include "registry.h"
#include "tcp_server.h"
#include "utils.h"

#include <cstdlib>
#include <iostream>

using namespace std;

void on_client_data(SockData* c_data, TcpSocket* c_sock);
string commit(SockData* c_data);
bool test_commit(SockData* c_data, string& res);

int main(int argc, char* argv[])
{
    SockData client_data;
    SockDataCb client_sock_cb;
    client_sock_cb.subscribe(&on_client_data, &client_data);

    TcpServer server(76542, &client_sock_cb);
    try {
        server.start();
    } catch (Exception ex) {
        Utils::print_error("server_main: "
            + ex.get_message());
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

void on_client_data(SockData* c_data, TcpSocket* c_sock)
{
    //TODO: remove
    //cout << c_data->filename << endl;

    string result;
    // test if operation is valid before
    // commiting
    if (test_commit(c_data, result))
        result = commit(c_data);

    c_sock->send(result);
}

string commit(SockData* c_data) 
{
    Registry& reg = Registry::instance();

    string result;
    switch(c_data->cmd_t) {
        case E_CMD_CREATE:
            result = reg.add_file(c_data->filename);
            break;
        case E_CMD_SEEK:
            result = reg.seek_file(c_data->filename, c_data->input.number);
            break;
        case E_CMD_READ:
            result = reg.read_file(c_data->filename, c_data->input.number);
            break;
        case E_CMD_WRITE:
            result = reg.write_file(c_data->filename, c_data->input.data); 
            break;
        case E_CMD_DELETE:
            result = reg.remove_file(c_data->filename);
        default:
            break;
    }
    return result;
}

bool test_commit(SockData* c_data, string& result) 
{
    Registry& reg = Registry::instance();

    bool success = false;;
    
    switch(c_data->cmd_t) {
        case E_CMD_CREATE:
            success = reg.test_add_file(c_data->filename, result);
            break;
        case E_CMD_SEEK:
            success = reg.test_seek_file(c_data->filename,
                c_data->input.number, result);
            break;
        case E_CMD_READ:
            success = reg.test_read_file(c_data->filename,
                c_data->input.number, result);
            break;
        case E_CMD_WRITE:
            success = reg.test_write_file(c_data->filename, result); 
            break;
        case E_CMD_DELETE:
            success = reg.test_remove_file(c_data->filename, result);
        default:
            break;
    }
    return success;
}
