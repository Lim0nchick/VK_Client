//
// Created by root on 10/30/16.
//

#include <iostream>
#include <map>
#include "client.hpp"
#include <string>
using namespace std;
int main()
{
    string access_token="713052e147c58cd93b85a180b76561f0225b4c84f91af051cf411d641c25484a4d14ad0b68b9eb113bf87";
    //cout << "Access_token: ";
    //cin >> access_token;
    VK::VK_Client data({{"token", access_token }});
    data.check_connection();
    return 0;
}
