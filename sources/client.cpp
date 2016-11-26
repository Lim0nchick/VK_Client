//
// Created by root on 10/30/16.
//

#include <iostream>
#include <curl/curl.h>
#include <exception>
#include "VK/client.hpp"
#include "VK/json.hpp"
using namespace std;
using namespace nlohmann;

namespace VK
{

    auto VK_Client::check_connection() -> bool
    {
        string link = "";
        CURL *curl = curl_easy_init();
        if (curl)
        {
            string data_to_send = "access_token=" + settings_["token"] + "&v=5.59";
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getProfileInfo?");
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_to_send.length());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, link);
            res = curl_easy_perform(curl);
            if (res == CURLE_OK)
            {
                try
                {
                    json j_obj = json::parse(link);
                    json j_response = j_obj["response"];
                    if (!j_response.is_null())
                    {
                        curl_easy_cleanup(curl);
                        return true;
                    }
                }
                catch (exception & error)
                {
                    cout << error.what() << endl;
                    return 0;
                }
            }
        }
    }

    auto VK_Client::audio_list() -> json
    {
        CURL *curl = curl_easy_init();
        if (curl)
        {
            string data_to_send = "access_token=" + settings_["token"] + "&v=5.59";
            CURLcode res;
            string link = "";
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getProfileInfo?");
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_to_send.length());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, link);
            res = curl_easy_perform(curl);
            if (res == CURLE_OK)
                try
                {
                    json j_result = json::parse(link);
                    json j_response = j_result["response"];

                    if (!j_response.is_null())
                    {
                        curl_easy_cleanup(curl);
                        return j_response;
                    }
                }
                catch (exception & error)
                {
                    cout << error.what() << endl;
                }
            curl_easy_cleanup(curl);
            return true;
        }
    }


    auto VK_Client::func(char* ptr, size_t size, size_t nmemb, string* link) -> size_t
    {
        *link += ptr;
        return size*nmemb;
    }
}