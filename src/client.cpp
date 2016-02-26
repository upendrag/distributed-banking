#include "constants.h"
#include "utils.h"

#include <iostream>

using namespace std;

void print_help(string);
void suggest_help(string);

int main(int argc, char* argv[])
{
    if (argc < 2) {
        Utils::print_error("Too few argumemts");
        suggest_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    string cmd(argv[1]);

    // Determine command type
    if (cmd == CMD_HELP) {
        print_help(argv[0]);
    } else if (cmd == CMD_TERMINATE) {
        //TODO: Implement server terminate;
    } else if (cmd == CMD_CREATE) {
        if (argc < 3) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            
        string filename(argv[2]);

        //TODO: remove print statements
        cout << "argument: " << filename << endl;

    } else if (cmd == CMD_SEEK) {
        if (argc < 3) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            
        string filename(argv[2]);
        int index;
        try {
            index = Utils::str_to_int(argv[3]);
        } catch (Exception ex) {
            Utils::print_error("Parsing seek index: " 
                + ex.get_message());
            exit(EXIT_FAILURE);
        }
        
        //TODO: remove prints statements
        cout << "argument: " << filename << endl;
        cout << "argument: " << index << endl;

    } else if (cmd == CMD_SEEK) {
        if (argc < 4) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            
        string filename(argv[2]);
        int index;
        try {
            index = Utils::str_to_int(argv[3]);
        } catch (Exception ex) {
            Utils::print_error("Parsing seek index: " 
                + ex.get_message());
            exit(EXIT_FAILURE);
        }
        
        //TODO: remove prints statements
        cout << "argument: " << filename << endl;
        cout << "argument: " << index << endl;

    } else if (cmd == CMD_READ) {
        if (argc < 4) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            
        string filename(argv[2]);
        int length;
        try {
            length = Utils::str_to_int(argv[3]);
        } catch (Exception ex) {
            Utils::print_error("Parsing read length: " 
                + ex.get_message());
            exit(EXIT_FAILURE);
        }
        
        //TODO: remove prints statements
        cout << "argument: " << filename << endl;
        cout << "argument: " << length << endl;

    } else if (cmd == CMD_WRITE) {
        if (argc < 4) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            
        string filename(argv[2]);
        string data(argv[3]);
        
        //TODO: remove prints statements
        cout << "argument: " << filename << endl;
        cout << "argument: " << data << endl;

    } else if (cmd == CMD_DELETE) {
        if (argc < 3) {
            Utils::print_error(ERR_INSUFF_ARGS);
            suggest_help(argv[0]);
            exit(EXIT_FAILURE);
        }            
        string filename(argv[2]);

        //TODO: remove print statements
        cout << "argument: " << filename << endl; 

    } else {
        Utils::print_error("Unknown option");
        suggest_help(argv[0]);
    }

    return 0;
}

void print_help(string app_name)
{
    cout << "usage: " << app_name << " <option> ..." << endl;
    cout << "options:" << endl;
    cout << "\t" <<  CMD_CREATE << " <filename>" << endl;
    cout << "\t" << CMD_SEEK << " <filename> <index>" << endl;
    cout << "\t" << CMD_READ << " <filename> <length>" << endl;
    cout << "\t" << CMD_WRITE << " <filename> <string>" << endl;
    cout << "\t" << CMD_DELETE << " <filename>" << endl;
    cout << "\t" << CMD_TERMINATE << endl;
    cout << "\t" << CMD_HELP << endl;
}

void suggest_help(string app_name)
{
    cout << "Run '" << app_name << " help' for usage and options" << endl;
}
