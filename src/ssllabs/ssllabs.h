//
// Created by burso on 3/20/16.
//

#ifndef LIBSSLLABS_SSLLABS_H
#define LIBSSLLABS_SSLLABS_H

#define SSLLABS_API_URL "https://api.ssllabs.com/api/v2"
#define SSLLABS_AGENT   "libssllabs/1.0"

class SSLlabs {
public:
    SSLlabs();
    ~SSLlabs();

    int analyze(const std::string domain);
    int getRootCertsRaw(const std::string &certs);
    int getInfoRaw(const std::string &info);
    int getStatusCodesRaw(const std::string &codes);

protected:
    int curl_read(const std::string &url, const std::string &data, long timeout = 30);

private:
};

#endif //LIBSSLLABS_SSLLABS_H
