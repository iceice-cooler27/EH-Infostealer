#ifndef CONNECTION_H
#define CONNECTION_H

#include "curl.h"

namespace cn {
    bool chk_svr_acc(const std::string url);
    bool sleep_await(const std::string url);
}

#endif
