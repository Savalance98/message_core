#ifndef Users_manager_H
#define Users_manager_H
#include <vector>
#include "models/User.h"
#include "db/db.h"
#include "http/http.h"

class Users_manager {

    public:
    // Core(std::shared_ptr<User> user_ , std::shared_ptr<db> db_ , std::shared_ptr<http_serv> http_);
    void send_message(std::string ip_2, std::string& message);
    void history(std::string ip_2);

    private:
    std::vector<std::string> parse_host;
    std::vector<std::string> parser(std::string ip_2);
    std::shared_ptr<User> user;
    std::shared_ptr<db> db;
    std::shared_ptr<http_serv> http_serv;

};

#endif