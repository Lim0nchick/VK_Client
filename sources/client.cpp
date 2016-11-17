//
// Created by root on 10/30/16.
//

#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include "VK/client.hpp"
#include "VK/json.hpp"
using namespace std;
using namespace nlohmann;

namespace VK
{

    string token = "access_token=55c2bf6da06b4b4b2c24cc5a21f291e67404517755e5a43097a6e232c9a2f19db6eab8831845c3ed6abc1";

    auto VK_Client::check_connection() -> bool
    {

        CURL *curl = curl_easy_init();
        if (curl)
        {

            string data_to_send = "access_token=" + settings_["token"] + "&v=5.59";
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getInfo?");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_to_send.length());

            long response_code;
            res = curl_easy_perform(curl);
            if (res == CURLE_OK) {
                long response_code;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                cout << endl;
                if (response_code >= 300 && response_code < 400)
                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
                if (response_code >= 400)
                    cout << "Error connection: " << response_code << endl;
                if (response_code >= 200 && response_code < 300)
                    cout << "Connected successfully" << endl;
            }


        }
        curl_easy_cleanup(curl);
    };

    auto VK_Client::friend_list() -> void
    {
        CURL *curl = curl_easy_init();
        if (curl)
        {
            string data_to_send = "extended=1&offset=5&count=4&access_token=" + settings_["token"] + "&v=5.59";
            CURLcode res;
            string link = "";
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/groups.get?");
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_to_send.length());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &link);
            res = curl_easy_perform(curl);
            if (res == CURLE_OK)
            {
                json j_result=json::parse(link.c_str());
                json j_resp = j_result["response"];
                if(!j_resp.empty())
                {
                    size_t count= j_resp["count"];
                    cout << "response {" << endl;
                    cout << "count: " << count << endl;
                    if (count)
                    {
                        
                    }
                }
            }
        }

    }
}