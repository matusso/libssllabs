//
// Created by burso on 3/20/16.
//

#ifndef LIBSSLLABS_SSLLABS_H
#define LIBSSLLABS_SSLLABS_H

#define SSLLABS_API_URL "https://api.ssllabs.com/api/v2"
#define SSLLABS_AGENT   "libssllabs/1.0"

#include <vector>

typedef struct labsInfo {
    std::string EngineVersion;
    std::string CriteriaVersion;
    int MaxAssessments;
    int CurrentAssessments;
    long NewAssessmentCoolOff;
    std::vector<std::string> Messages;
} labsInfo_t;

class SSLlabs {
public:
    SSLlabs();
    ~SSLlabs();

    long timeout;

    int analyze(const std::string domain);
    int getRootCertsRaw(const std::string &certs);

    int getInfo(const std::string &info);
    int getInfo(labsInfo_t &info);

    int getStatusCodes(const std::string &codes);

protected:
    int curl_read(const std::string &url, const std::string &data);

private:
};

#endif //LIBSSLLABS_SSLLABS_H
