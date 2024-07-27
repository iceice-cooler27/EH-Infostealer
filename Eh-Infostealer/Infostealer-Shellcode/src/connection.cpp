#include "connection.h"
#include <chrono>
#include <thread>

namespace cn {
    bool chk_svr_acc(const std::string url) {
        CURL* curl;
        CURLcode res;
        bool success = false;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);  // Only check the server without downloading anything

            res = curl_easy_perform(curl);
            if (res == CURLE_OK) {
                std::cout << "\n\nAccess to "+ url + " available. Server found."<< std::endl;
                success = true;
            } else {
                std::cerr << "Failed to access web server: " << curl_easy_strerror(res) << std::endl;
            }
            curl_easy_cleanup(curl);
        }
        return success;
    }

    bool sleep_await(const std::string url) {
        // Checks every 15 seconds, Sleep for at most 5 minute
        for (int i=0; i<20; ++i) {
            std::cout << "Await Time(s): " << i*15 << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(15));
            if (chk_svr_acc(url)){
                return false;
            }
        }
        return true;
    }
}