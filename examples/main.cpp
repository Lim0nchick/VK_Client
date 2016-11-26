//
// Created by root on 10/30/16.
//

#include <iostream>
#include <map>
#include "VK/client.hpp"
#include "VK/json.hpp"
#include "curl/curl.h"
#include <string>
#include <clocale>

using namespace std;
using namespace VK;
void get_info(const json & account);
int main()
{
    setlocale(LC_ALL, "rus");
    //CURL *curl = curl_easy_init();
    string access_token;
    cout << "Access_token: ";
    //cin >> access_token;
    access_token = "789369e433eb09f9673e8ce8e457d82c0d55710bfd2ddcbdfdd5eca4a61bab64b2cc6dc2a5e0bcb4119e8";
    VK_Client data({{"token", access_token }});
    if (data.check_connection())
        cout << "Connected successfully" << endl << endl;
    //string command;
    //cout << "Write command: ";
    //cin >> command;
    get_info(data.audio_list());






    //curl_easy_cleanup(curl);
    return 0;
}

void get_info(const json & account)
{
    try
    {
        json jsn_fname = account["first_name"];
        if (!jsn_fname.is_null())
            cout << "first name: " << jsn_fname.begin().value() << endl;

        json jsn_lname = account["last_name"];
        if (!jsn_lname.is_null())
            cout << "last name: " << jsn_lname.begin().value() << endl;

        json jsn_bdate = account["bdate"];
        if (!jsn_bdate.is_null())
            cout << "birthday: " << jsn_bdate.begin().value() << endl;

        json jsn_sex = account["sex"];
        if (!jsn_sex.is_null())
            cout << "sex: " << ((int) jsn_sex.begin().value() == 1 ? "female" : "male") << endl;

        json jsn_hometown = account["home_town"];
        if (!jsn_hometown.is_null())
            cout << "home town: " << jsn_hometown.begin().value() << endl;
    }
    catch (const exception &error)
    {
        cout << error.what() << endl;
    }
}