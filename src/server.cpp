#include "config.h"
#include "constants.h"
#include "registry.h"
#include "tcp_server.h"
#include "utils.h"

#include <cstdlib>
#include <iostream>

using namespace std;

void on_client_data(SockData* c_data, TcpSocket* c_sock);
void commit(SockData* c_data, ReplyMessage& r_msg);
bool test_commit(SockData* c_data, ReplyMessage& r_msg);
bool test_commit_peers(SockData* c_data, ReplyMessage& r_msg);
void commit_peers(SockData* c_data, ReplyMessage& r_msg, MSG_TYPE msg_t);

static TcpConfig my_conf;
static vector<TcpConfig> others;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        Utils::print_error("usage: ./server <number>[1-3]");
        exit(EXIT_FAILURE);
    }

    // read config
    Config config(CONFIG_FILE);
    try {
        config.create();

        int server_num = Utils::str_to_int(argv[1]);
        if (server_num > 3)
            throw Exception("Undefined server number");
        for (int i = 1; i <= NUM_OF_SERVERS; ++i) {
            TcpConfig cfg = config.getTcpConfig(i);
            if (i == server_num){
                my_conf = cfg;
                continue;
            }
            others.push_back(cfg);
        }

    } catch (...) {
        Utils::print_error("unable to read config");
        exit(EXIT_FAILURE);
    }

    // init callbacks
    SockData client_data;
    SockDataCb client_sock_cb;
    client_sock_cb.subscribe(&on_client_data, &client_data);

    // start TCP server
    TcpServer server(my_conf.port, &client_sock_cb);
    try {
        cout << "Started listening on " << my_conf.host
            << ":" << my_conf.port;
        cout.flush();
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
    ReplyMessage r_msg;

    switch (c_data->msg_t) {

        case CLIENT_TO_SERVER:
            if (test_commit(c_data, r_msg)
                && test_commit_peers(c_data, r_msg)) {
                // all good, commit peers and myself
                commit_peers(c_data, r_msg,
                    SERVER_TO_SERVER_COMMIT);
                commit(c_data, r_msg);
            }
            break;

        case SERVER_TO_SERVER_TEST_COMMIT:
            test_commit(c_data, r_msg);
            break;

        case SERVER_TO_SERVER_COMMIT:
            commit(c_data, r_msg);
            break;

        default:
            break;
    }  

    r_msg.server_num = my_conf.number;
    c_sock->send(&r_msg, sizeof(ReplyMessage));
}

void commit(SockData* c_data, ReplyMessage& r_msg) 
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
        case E_CMD_TERMINATE:
            reg.clear_seek_positions();
        default:
            break;
    }
    r_msg.result = true;
    Utils::copy_str_to_arr(result, r_msg.message, MAX_WRITE_LEN);
}

bool test_commit(SockData* c_data, ReplyMessage& r_msg) 
{
    Registry& reg = Registry::instance();

    bool success = false;;
    
    std::string result;
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
            break;
        case E_CMD_TERMINATE:
            // terminate should be always successful
            success = true;
            break;
        default:
            break;
    }
    r_msg.result = success;
    Utils::copy_str_to_arr(result, r_msg.message, MAX_WRITE_LEN);

    return success;
}

bool test_commit_peers(SockData* c_data, ReplyMessage& r_msg)
{
    // assume success
    r_msg.result = true;

    commit_peers(c_data, r_msg, SERVER_TO_SERVER_TEST_COMMIT);

    return r_msg.result;
}

void commit_peers(SockData* c_data, ReplyMessage& r_msg,
    MSG_TYPE msg_t)
{
    // no need to contact peers for read operation
    if (c_data->cmd_t == E_CMD_READ ||
        c_data->cmd_t == E_CMD_TERMINATE)
        return;

    c_data->msg_t = msg_t;
    
    for (int i = 0; i < (int)others.size(); ++i) {
        TcpConfig cfg = others.at(i);
        TcpSocket client(cfg.port, cfg.host);
        try {
            client.connect();
            client.send(c_data, sizeof(SockData));
            client.receive(&r_msg, sizeof(ReplyMessage));
            client.close();
        } catch (Exception ex) {
            r_msg.result = false;
            Utils::copy_str_to_arr(FAIL_PEER_COMM, 
                r_msg.message, MAX_WRITE_LEN);
            Utils::print_error(ex.get_message());
            break;
        }
    }
}

