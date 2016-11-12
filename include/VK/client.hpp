//
// Created by root on 10/30/16.
//

#ifndef VK_CLIENT_HPP
#define VK_CLIENT_HPP

#endif //VK_CLIENT_HPP-

#include <string>
#include <map>

namespace VK
{
    using namespace std;
    class Client
    {
    public:
        using dict_t = map<string, string>;
        Client(dict_t settings);
        auto check_connection() -> bool;
    };
}
