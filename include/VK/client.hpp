//
// Created by root on 10/30/16.
//

#include <string>
#include <map>
#include "json.hpp"
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
        auto friend_list() -> json;
        auto func(char* ptr, size_t size, size_t nmemb, string* link)->size_t;
    private:
        dict_t settings_;
    };
}
