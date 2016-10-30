//
// Created by root on 10/30/16.
//

#ifndef LIMEGRAM_CLIENT_HPP
#define LIMEGRAM_CLIENT_HPP

#endif //LIMEGRAM_CLIENT_HPP-

#include <string>
#include <map>

namespace LimeGram
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