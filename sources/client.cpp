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
    string link = "";
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
                }
            }

            /*if (res == CURLE_OK)
            {
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                cout << endl;
                if (response_code >= 300 && response_code < 400)
                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
                if (response_code >= 400)
                    cout << "Error connection: " << response_code << endl;
                if (response_code >= 200 && response_code < 300)
                    cout << "Connected successfully" << endl;
            }*/
        }
    }

    auto VK_Client::friend_list() -> json
    {
        CURL *curl = curl_easy_init();
        if (curl)
        {
            string data_to_send = "extended=1&offset=5&count=4&access_token=" + settings_["token"] + "&v=5.59";
            CURLcode res;

            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/groups.get?");
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_to_send.length());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &link);
            res = curl_easy_perform(curl);
            if (res == CURLE_OK)
            {
                try
                {
                    json j_result=json::parse(link.c_str());
                    json j_response = j_result["response"];
                    if (!j_response.is_null())
                    {
                        size_t count= j_response["count"];
                        cout << "response {" << endl;
                        cout << "count: " << count << endl;
                        if (count)
                        {
                            json j_obj = j_response["items"];
                            for(json::iterator iter = j_obj.begin(); iter != j_obj.end(); ++iter)
                            {
                                json j_id = iter.value()["id"];		    cout << "id: " << j_id << endl;
                                json j_sort = iter.value()["order"];	cout << "sort by " << j_sort << endl;
                                json j_list_id=iter.value()["list_id"];	cout << "list_id: " << j_list_id << endl;
                                json j_count=iter.value()["count"]; 	    cout << "count: " << j_count << endl;
                                json j_offset=iter.value()["offset"]; 	cout << "offset" << j_offset << endl;
                                json j_sub_obj = j_response["fields"];
                                for (json::iterator iter1 = j_sub_obj.begin(); iter1 != j_sub_obj.end(); ++iter1)
                                {
                                    json j_uid = iter1.value()["uid"];                cout << "uid:  " << j_uid << endl;
                                    json j_first_name = iter1.value()["first_name"];  cout << j_first_name;
                                    string j_last_name = iter1.value()["last_name"];    cout << " " << j_last_name << endl;
                                    json j_nickname = iter1.value()["nickname"];      cout << "nickname:  " << j_nickname << endl;
                                    json j_sex = iter1.value()["sex"];                cout << "sex:  " << j_sex << endl;
                                    json j_bdate = iter1.value()["bdate"];            cout << "birthdate:  " << j_bdate << endl;
                                    json j_city = iter1.value()["city"];              cout << "city: " << j_city << endl;
                                    json j_country = iter1.value()["country"];         cout << "country: " << j_country << endl;
                                    json j_timezone = iter1.value()["timezone"];      cout << "timezone: " << j_timezone << endl;
                                    json j_photo = iter1.value()["photo"];            cout << "photo:  " << j_photo << endl;
                                    json j_photo_medium = iter1.value()["photo_medium"]; cout << "med_foto: " << j_photo_medium << endl;
                                    json j_photo_big = iter1.value()["photo_big"];       cout << "big_foto" << j_photo_big << endl;
                                    json j_dom = iter1.value()["domain"];                cout << "domain: " << j_dom << endl;
                                    json j_mob = iter1.value()["has_mobile"];            cout << "mobile: " << j_mob << endl;
                                    json j_rate = iter1.value()["rate"];                 cout << "rate: " << j_rate << endl;
                                    json j_contacts = iter1.value()["contacts"];         cout << "contacts: " << j_contacts << endl;
                                    json j_edu = iter1.value()["education"];             cout << "education: " << j_edu << endl;
                                }
                                json j_name_case= iter.value()["name_case"];             cout << "name_case" << j_name_case << endl << endl;
                            }
                            cout << "}" << endl;
                        }
                        curl_easy_cleanup(curl);
                        return true;
                    }

                }
                catch (exception & error)
                {
                    cout << error.what() << endl;
                }
            }
        }
        curl_easy_cleanup(curl);
    }

    auto VK_Client::func(char* ptr, size_t size, size_t nmemb, string* link) -> size_t
    {
        *link += ptr;
        return size*nmemb;
    }
}