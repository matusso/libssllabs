//
// Created by burso on 3/20/16.
//

#include <iostream>
#include <ssllabs/ssllabs.h>

int main() {
    SSLlabs sl;
    std::string certs;
    std::string info;

    sl.getRootCertsRaw(certs);
    sl.getInfoRaw(info);

    std::cout << certs << std::endl;
    std::cout << info << std::endl;

    return 0;
}