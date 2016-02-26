#include "constants.h"
#include "utils.h"

#include <climits>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

void print_help(void);
vector<string> split_str(string str, string delim);

int main()
{
    string cmd_str;
    
    print_help();

    while (true) {
        cout << ">> ";
        getline(cin, cmd_str);
        vector<string> cmd_args = split_str(cmd_str, " ");
        if (cmd_args.size() == 0)
            continue;

        // Determine command type
        if (cmd_args.front() == CMD_HELP)
            print_help();
        else if (cmd_args.front() == CMD_TERMINATE)
            return 0;
        else if (cmd_args.front() == CMD_CREATE) {
            if (cmd_args.size() < 2) {
                Utils::print_error(ERR_INSUFF_ARGS);
                continue;
            }            
            string filename = cmd_args.at(1);

            //TODO: remove print statements
            cout << "argument: " << filename << endl; 
        }
        else if (cmd_args.front() == CMD_SEEK) {
            if (cmd_args.size() < 3) {
                Utils::print_error(ERR_INSUFF_ARGS);
                continue;
            }            
            string filename = cmd_args.at(1);
            int index;
            try {
                index = Utils::str_to_int(cmd_args.at(2));
            } catch (Exception ex) {
                Utils::print_error("Parsing seek index: " 
                    + ex.get_message());
                continue;
            }
            
            //TODO: remove prints statements
            cout << "argument: " << filename << endl;
            cout << "argument: " << index << endl;
        }
        else
            cout << "Invalid command!" << endl;
    }

    return 0;
}

void print_help(void)
{
    cout << "COMMAND LIST:" << endl;
    cout << CMD_CREATE << " <filename>" << endl;
    cout << CMD_SEEK << " <filename> <index>" << endl;
    cout << CMD_READ << " <filename> <length>" << endl;
    cout << CMD_WRITE << " <filename> <string>" << endl;
    cout << CMD_DELETE << " <filename>" << endl;
    cout << CMD_TERMINATE << endl;
    cout << CMD_HELP << endl;
}

vector<string> split_str(string str, string delim)
{
    istringstream iss(str);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(tokens));
    return tokens;
}
