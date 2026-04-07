//
// Created by burso on 3/22/16.
//

#include <iostream>

#include <ssllabs/ssllabs.h>

#include "parsers.h"

namespace ssllabs {

    int SSLlabs::analyze(const std::string &domain, std::string &data,
                         bool publish, bool startNew, bool fromCache, bool ignoreMismatch) {
        std::string command("/analyze?host=");

        command += domain;
        if (startNew && fromCache) {
            std::cerr << "could not use startNew and fromCache at the same time\n";
            return -1;
        }

        if (publish) {
            command += "&publish=on";
        }

        if (startNew) {
            command += "&startNew=on";
        }

        if (fromCache) {
            command += "&fromCache=on";
        }
        else {
            if (ignoreMismatch) {
                command += "&ignoreMismatch=on";
            }
        }

        return curl_read(command, data);
    }

    int SSLlabs::analyze(const std::string &domain, labsReport_t &report,
                         bool publish, bool startNew, bool fromCache, bool ignoreMismatch) {
        std::string command("/analyze?host=");
        std::string data;

        command += domain;
        if (startNew && fromCache) {
            std::cerr << "could not use startNew and fromCache at the same time\n";
            return -1;
        }

        if (publish) {
            command += "&publish=on";
        }

        if (startNew) {
            command += "&startNew=on";
        }

        if (fromCache) {
            command += "&fromCache=on";
        }
        else {
            if (ignoreMismatch) {
                command += "&ignoreMismatch=on";
            }
        }

        if (curl_read(command, data) != 0) {
            return -1;
        }

        return detail::parseAnalyzeResponse(data, report);
    }

}
