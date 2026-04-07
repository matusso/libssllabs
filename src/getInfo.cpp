//
// Created by burso on 3/21/16.
//

#include <ssllabs/ssllabs.h>

#include "parsers.h"

namespace ssllabs {

    int SSLlabs::getInfo(std::string &data) {
        curl_read("/info", data);
        return 0;
    }

    int SSLlabs::getInfo(labsInfo_t &info) {
        std::string data;
        if (curl_read("/info", data) != 0) {
            return -1;
        }

        return detail::parseInfoResponse(data, info);
    }

}
