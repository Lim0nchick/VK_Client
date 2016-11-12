//
// Created by root on 10/30/16.
//

#include <iostream>
<<<<<<< HEAD:examples/main1.cpp
#include <map>
#include "client.hpp"
#include <string>
=======
//#include <locale.h>
>>>>>>> 77f10556c6a63f63a3cb59b489af3a596e904884:examples/main.cpp
using namespace std;
int main()
{
<<<<<<< HEAD:examples/main1.cpp
    string access_token;
    cout << "Access_token: ";
    cin >> access_token;
    VK::VK_Client data({{"token", access_token }});
    data.check_connection();
=======
    //setlocale(LC_ALL, "Russian");
    CURL *curl;
    CURLcode res;
    long response_code;
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; ru; rv:1.9.0.1) Gecko/2008070208");
    if (curl)
    {

        curl_easy_setopt(curl, CURLOPT_URL, "https://vk.com");
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        cout << response_code << endl;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) cout << "curl_easy_perform() failed:" << curl_easy_strerror(res) << endl;
        cout << "\n\n\n\n";


        curl_easy_setopt(curl, CURLOPT_USERPWD, "[lim0nchick@yandex.ru]:[11797277359LImo]");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);cout << endl;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) cout << "curl_easy_perform() failed:" << curl_easy_strerror(res) << endl;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        cout << response_code << endl;




        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
>>>>>>> 77f10556c6a63f63a3cb59b489af3a596e904884:examples/main.cpp
    return 0;
}
