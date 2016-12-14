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
        auto VK_Client::friends_getOnline() -> json;
        void get_feed(const json & account);
        auto VK_Client::thread_func(int _m, string _f) -> bool;
        static auto func(char* ptr, size_t size, size_t nmemb, string* link) -> size_t;
    private:
        dict_t settings_;
    };

    struct friend_online
    {
        json user_id;
        json list_id;
        json online_mobile;
        json order;
        json offset;
        friend_online() : user_id("unknown"), list_id("unknown"), online_mobile("unknown"), order("unknown"), offset("unknown") {};
        friend_online(json j_user_id, json j_list_id, json j_online_mobile, json j_order, json j_offset) : user_id(j_user_id), list_id(j_list_id), online_mobile(j_online_mobile), order(j_order), offset(j_offset) {};

        friend auto operator == (const friend_online first_friend, const friend_online second_friend) -> bool
        {
            if (first_friend.user_id == second_friend.user_id && first_friend.list_id == second_friend.list_id && first_friend.online_mobile == second_friend.online_mobile && first_friend.order == second_friend.order && first_friend.offset == second_friend.offset)
                 return true;
            else return false;
        }

        auto print_friend_online() -> void
        {
            cout << "ids: " << list_id.value() << endl;
            cout << "id: " << user_id.begin().value() << endl;
            cout << "online_mobile: " << online_mobile.begin().value() << endl;
            cout << "order: " << order.begin().value() << endl;
            cout << "offset: " << offset.begin().value() << endl;
        }

        ~friend_online() {};
    };
}