//
// Created by root on 10/30/16.
//

#include <iostream>
#include <map>
#include "VK/client.hpp"
#include <string>

using namespace std;
using namespace VK;

int main()
{
    string access_token;
    cout << "Access_token: ";
    cin >> access_token;
    VK_Client data({{"token", access_token }});
    data.check_connection();
    string command;
    cout << "Write command: ";
    cin >> command;
    




    return 0;
}
