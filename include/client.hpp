//
// Created by root on 10/30/16.
//

/*#include <map>
#include <string>
namespace Vk
{
    class VkClient
    {
    public:
        using dict_t = std::map<std::string, std::string>;

        VkClient() {};
        VkClient(dict_t settings) : settings_(settings) {};
        auto check_connection() -> bool;

    private:
        dict_t settings_;
    };
}*/

#include <string>
#include <map>

namespace VK
{
    class VK_Client
    {
    public:
        using dict_t = std::map<std::string, std::string>;
        VK_Client(dict_t settings) : _settings(settings) {};
        auto check_connection() -> bool;
        auto get_groups(size_t count) -> void;
    private:
        dict_t _settings;
        static auto write_data(char* buffer, size_t size, size_t nmemb, std::string& userp) -> size_t;
    };
}
