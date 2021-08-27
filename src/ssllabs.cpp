//
// Created by burso on 3/20/16.
//

#include <iostream>
#include "../include/ssllabs/ssllabs.h"

namespace ssllabs {
    static size_t writeCallback(char *buf, size_t size, size_t nmemb, void *up) {
        size_t realsize = size * nmemb;

        std::string *mem = (std::string *) up;
        mem->append(buf);

        return realsize;
    }

    SSLlabs::SSLlabs() {
        timeout = 30; // * default timeout set to 30 seconds
        curl_global_init(CURL_GLOBAL_ALL);
    }

    SSLlabs::~SSLlabs() {
        curl_global_cleanup();
    }

    int SSLlabs::getRootCertsRaw(const std::string &certs) {
        curl_read("/getRootCertsRaw", certs);
        return 0;
    }

    int SSLlabs::getStatusCodes(const std::string &codes) {
        curl_read("/getStatusCodes", codes);
        return 0;
    }

    void SSLlabs::verifyCurlStatus(CURLcode code) {
        if (code != CURLE_OK) {
            std::cerr << "curl_setup failed: " << curl_easy_strerror(code) << "\n";
        }
    }

    int SSLlabs::curl_read(const std::string &command, const std::string &data) {
        CURLcode code(CURLE_OK);
        CURL *curl = curl_easy_init();
        std::string url(SSLLABS_API_URL);

        url += command;

        if (curl) {
            code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
            verifyCurlStatus(code);

            code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &data);
            verifyCurlStatus(code);

            code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
            verifyCurlStatus(code);

            code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            verifyCurlStatus(code);

            code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
            verifyCurlStatus(code);

            code = curl_easy_setopt(curl, CURLOPT_USERAGENT, SSLLABS_AGENT);
            verifyCurlStatus(code);

            code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            verifyCurlStatus(code);

            code = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
            verifyCurlStatus(code);

            code = curl_easy_perform(curl);
            verifyCurlStatus(code);
            
            curl_easy_cleanup(curl);
        }

        return code;
    }
}