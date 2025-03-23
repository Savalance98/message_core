#include "User.h"
#include <string>


Users::Users(std::string Users_host_): users_host(Users_host_) {};



std::string Users::get_host() {
    return users_host;
}