//
// Created by root on 10/30/16.
//

#include <string>
#include <map>
#include "json.hpp"
#include "curl/curl.h"
using namespace std;
using namespace nlohmann;

namespace VK
{
    class VK_Client
    {
    public:
        using dict_t = map<string, string>;

        VK_Client() {};
        VK_Client(dict_t settings) : settings_(settings) {};
        auto check_connection() -> bool;
        auto getProfileInfo() -> json;
        void get_info(const json & account);
        json VK_Client::feed();
        void get_feed(const json & account);
        static auto func(char* ptr, size_t size, size_t nmemb, string* link) -> size_t;
    private:
        dict_t settings_;
    };
}