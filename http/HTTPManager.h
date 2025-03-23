#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H
#include <vector>
// #include "models/User.h"
#include "db/db.h"
#include "http/http.h"

class HTTP_manager {
public:
    explicit HTTP_manager(std::shared_ptr<http_server> server_);
    void stop_server();

private:
    std::shared_ptr<http_server> server;

};

#endif