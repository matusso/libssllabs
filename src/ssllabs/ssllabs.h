//
// Created by burso on 3/20/16.
//

#ifndef LIBSSLLABS_SSLLABS_H
#define LIBSSLLABS_SSLLABS_H

#define SSLLABS_API_URL "https://api.ssllabs.com/api/v2"
#define SSLLABS_AGENT   "libssllabs/1.0"

class SSLlabs {
public:
    SSLlabs() {};
    ~SSLlabs() {};

    int analyze(const std::string &domain);

protected:
    int curl_read(const std::string &url, std::string &data, long timeout = 30);

private:
};

#endif //LIBSSLLABS_SSLLABS_H
