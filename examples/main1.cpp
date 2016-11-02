//
// Created by root on 10/30/16.
//
#include <curl/curl.h>
#include <iostream>
#include <clocale>
using namespace std;
int main ()
{
    setlocale(0, "1251");
    CURL *curl;
    CURLcode res;
    long response_code;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux amd64; rv:14.0) Gecko/20100101 Firefox/14.0.1");
    if (curl)
    {

        curl_easy_setopt(curl, CURLOPT_URL, "https://vk.com");
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        cout << response_code << endl;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) cout << "curl_easy_perform() failed:" << curl_easy_strerror(res) << endl;
        cout << "\n\n\n\n";


        curl_easy_setopt(curl, CURLOPT_USERPWD, "[Lim0nchick@yandex.ru]:[11797277359LImo]");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);cout << endl;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) cout << "curl_easy_perform() failed:" << curl_easy_strerror(res) << endl;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        cout << response_code << endl;














        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
