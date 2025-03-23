#ifndef COREDEPENDENCIES_H
#define COREDEPENDENCIES_H
#include <iostream>
// #include "models/User.h"
#include "db/db.h"
#include "http/http.h"


class CoreDependencies {

    public:
    CoreDependencies(std::shared_ptr<DB> db_ , std::shared_ptr<http_server> http_);
    // std::shared_ptr<Users> user;
    std::shared_ptr<DB> db;
    std::shared_ptr<http_server> http_serv;

};

#endif