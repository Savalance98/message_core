#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <vector>
// #include "models/User.h"
#include "db/db.h"
#include "http/http.h"

class DB_manager {

    public:
    // Core(std::shared_ptr<User> user_ , std::shared_ptr<db> db_ , std::shared_ptr<http_serv> http_);
    // void send_message(std::string ip_2, std::string& message);
    DB_manager(std::shared_ptr<DB>db_);
    void history(const std::string& ip_2);

    private:
    std::shared_ptr<DB> db;
    // std::vector<std::string> parse_host;
    // std::vector<std::string> parser(std::string ip_2);

};

#endif