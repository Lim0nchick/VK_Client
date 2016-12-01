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
#include <thread>

using namespace std;
using namespace VK;

int main()
{
    setlocale(LC_ALL, "rus");
    //CURL *curl = curl_easy_init();
    string access_token;
    cout << "Access_token: ";
    //cin >> access_token;
    access_token = "af4c1a9673da3d3d681e816514134661005908bb3feaee2639d2952b40836889e78a8ab915cf2493f8e35";
    VK_Client data({{"token", access_token }});
    if (data.check_connection())
        cout << "Connected successfully" << endl << endl;
    //string command;
    //cout << "Write command: ";
    //cin >> command;
    get_info(data.getProfileInfo());

    int n;
    cout << "input number of thread: " << endl;
    cin >> n;
    if (n < 1 || n > thread::hardware_concurrency())
        cout << "you max use " << thread::hardware_concurrency() << " threads" << endl;
    else 
    {
        vector<thread> threads;
        for (int i=0; i<n; i++)
            threads.push_back(thread(get_feed, feed, n, argc == 2 && strcmp(argv[1], "-v") == 0, i));
        for (int i=0; i<n; i++)
            if (threads[i].joinable())
                threads[i].join();
    }

    



    //curl_easy_cleanup(curl);
    return 0;
}