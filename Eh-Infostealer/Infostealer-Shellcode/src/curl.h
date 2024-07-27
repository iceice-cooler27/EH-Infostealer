#ifndef CURL_H
#define CURL_H

#include "../include/lib.h"
#include "copy-upload.h"
#include <curl/curl.h>
#include <csignal>

static size_t writecallback(void* contents, size_t size, size_t nmemb, void* userp);
namespace crlu {
    static int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
    void curl_upload(const std::string url, std::vector<up::fldir> dirVec);
}

#endif
