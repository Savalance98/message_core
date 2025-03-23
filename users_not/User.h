#ifndef USER_H
#define USER_H
#include <string>

class Users {
    public:
    Users(std::string ip_);

    std::string get_host();
    // void get_history();
    private :
    std::string users_host;
    // std::string password;
};

#endif