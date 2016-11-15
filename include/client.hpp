//
// Created by root on 10/30/16.
//

#include <string>
#include <map>
#include "json.h"
using namespace std;

namespace VK
{
    class VK_Client
    {
    public:
        using dict_t = map<string, string>;
        VK_Client(dict_t settings) : _settings(settings) {};
        auto check_connection() -> bool;
        auto get_groups(size_t count) -> void;
    private:
        dict_t _settings;
        static auto write_data(char* buffer, size_t size, size_t nmemb, string& userp) -> size_t;
    };
}
