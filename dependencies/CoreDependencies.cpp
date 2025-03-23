#include "CoreDependencies.h"

CoreDependencies::CoreDependencies(std::shared_ptr<DB> db_, std::shared_ptr<http_server> http_): db(db_), http_serv(http_) {};