//
// Created by root on 10/30/16.
//

#include <iostream>
#include <curl/curl.h>
#include "client.hpp"
using namespace std;
namespace VK
{

    auto VK_Client::check_connection()-> bool
    {

        CURL *curl = curl_easy_init();
        if (curl)
        {
            string data_to_send = "access_token=713052e147c58cd93b85a180b76561f0225b4c84f91af051cf411d641c25484a4d14ad0b68b9eb113bf87&v=5.59";
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/users.get?");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.c_str());

            long response_code;
            res = curl_easy_perform(curl);
            if (res == CURLE_OK)
            {
                long response_code;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
		cout << endl;
		if (response_code>=300 && response_code<400)
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		if (response_code >=400)
			cout << "Error connection: " << response_code << endl;
                if (response_code >= 200 && response_code < 300)
	                cout << "Connected successfully" << endl;
            }


        }
        curl_easy_cleanup(curl);
    }
};
