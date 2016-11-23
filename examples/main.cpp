//
// Created by root on 10/30/16.
//

#include <iostream>
#include <map>
#include "VK/client.hpp"
#include "curl/curl.h"
#include <string>
#include <clocale>

using namespace std;
using namespace VK;

int main()
{
    setlocale(LC_ALL, "rus");
    //CURL *curl = curl_easy_init();
    string access_token;
    cout << "Access_token: ";
    cin >> access_token;
    VK_Client data({{"token", access_token }});
    data.check_connection();
    //string command;
    //cout << "Write command: ";
    //cin >> command;
    data.friend_list();






    //curl_easy_cleanup(curl);
    return 0;
}
