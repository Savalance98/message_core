#include "HTTPManager.h"


HTTP_manager::HTTP_manager(std::shared_ptr<http_server> server_) : server(server_) {}


void HTTP_manager::stop_server() {
    server->stop();
}