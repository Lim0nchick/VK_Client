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

    mutex _mutex;
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

    auto VK_Client::friends_getOnline() -> json
    {
         CURL *curl = curl_easy_init();
        if (curl)
        {
            string data_to_send = "access_token=" + settings_["token"] + "&v=5.59";
            CURLcode res;
            string link = "";
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/friends.getOnline");
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
                    json j_result = json::parse(link);
                    json j_response = j_result["response"];

                    json items = response["items"];
                    for (json::iterator it = items.begin(); it != items.end(); ++it)
                    {
                        json id = it.value()["user_id"];             
                        json list_id = it.value()["list_id"]; 
                        json online_mobile = it.value()["online_mobile"];
                        json order = it.value()["order"];
                        json offset = it.value()["offset"];
                        if (!user_id.is_null() && !list_id.is_null() && !online_mobile.is_null() && !order.is_null() && !offset.is_null())
                        {
                            friend_online _friend(user_id, list_id, online_mobile, order, offset.);
                            friend_list.push_back(_friend);
                        }

                    }
                }
                catch (exception & error)
                {
                    cout << error.what() << endl;
                }
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

    auto VK_Client::get_friend_thread(int _n) -> void
    {
        n = _n;
        if (n < 1 && n > thread::hardware_concurrency())
        {
            cout << "Неверное кол-во потоков" << endl;
            return;
        }
        string v = "";
        cout << "Flag: " << endl;
        cin >> f;
        if (f != "f" && f != "F" && v != "")
        {
            cout << "Error: unknown flag" << endl; 
            return ;
        }
        for (int i = 0; i < n; i++)
        {
            vec_thread.push_back(thread(&VK_Client::thread_func,this, i,f));
        }
        for (int i = 0; i < n; i++)
        {
            if (vec_thread[i].joinable())
                vec_thread[i].join();
        }
        return ;
}

    auto  VK_Client::thread_func(int _m, string _f) -> bool
    {
        for (int i = _m; i < friend_list.size(); i = i + n)
        {
            lock_guard<mutex> lock(_mutex);
            if (_f == "f" || _f == "F") 
            {
                cout << endl << "№" << i << endl << "thread_id " << this_thread::get_id() << endl;
            }
                cout << "USER : "; friend_list[i].PrintFriend();
                this_thread::sleep_for(chrono::milliseconds(1800));
        }
        return true;
    }

    auto Client::func(char *data, size_t size, size_t nmemb, std::string &buff) -> size_t
    {
        int result = 0;

        if (buff.c_str())
        {
            buff.append(data, size * nmemb);
            result = size * nmemb;
        }

        return result;
    }
}