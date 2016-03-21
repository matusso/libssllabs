//
// Created by burso on 3/20/16.
//

#include <iostream>
#include <ssllabs/ssllabs.h>

int main() {
    SSLlabs sl;
    std::string certs;
    std::string info;
    std::string codes;

    sl.getRootCertsRaw(certs);
    sl.getInfo(info);
    sl.getStatusCodes(codes);

    std::cout << codes << std::endl;

    return 0;
}