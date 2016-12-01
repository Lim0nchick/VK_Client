//
// Created by root on 10/30/16.
//

#include <iostream>
#include <curl/curl.h>
#include <exception>
#include "VK/client.hpp"
#include "VK/json.hpp"
#include <thread>
#include <mutex>


using namespace std;
using namespace nlohmann;

namespace VK
{

    mutex mutex;
    size_t thread_index = 0;
    
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

    auto VK_Client::getProfileInfo -> json
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

    auto VK_Client::feed() -> json
    {
         CURL *curl = curl_easy_init();
        if (curl)
        {
            string data_to_send = "access_token=" + settings_["token"] + "&v=5.59";
            CURLcode res;
            string link = "";
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/newsfed.get");
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

    void get_info(const json & account)
    {
        try
        {
            json j_first_name = account["first_name"];
            if (!j_first_name.is_null())
               cout << "first name: " << j_first_name.begin().value() << endl;

            json j_last_name = account["last_name"];
            if (!j_last_name.is_null())
                cout << "last name: " << j_last_name.begin().value() << endl;

            json j_bdate = account["bdate"];
            if (!j_bdate.is_null())
                cout << "birthday: " << j_bdate.begin().value() << endl;

            json j_sex = account["sex"];
            if (!j_sex.is_null())
                cout << "sex: " << ((int) j_sex.begin().value() == 1 ? "female" : "male") << endl;

            json j_home_town = account["home_town"];
            if (!j_home_town.is_null())
                cout << "home town: " << j_home_town.begin().value() << endl;
        }
        catch (const exception &error)
        {
            cout << error.what() << endl;
        }
    }

    void get_feed(const json & account)
    {

    }
    auto VK_Client::func(char* ptr, size_t size, size_t nmemb, string* link) -> size_t
    {
        *link += ptr;
        return size*nmemb;
    }
}