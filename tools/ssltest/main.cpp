//
// Created by burso on 3/20/16.
//

#include <iostream>
#include <ssllabs/ssllabs.h>

int main() {
    SSLlabs sl;
    labsInfo_t inf;

    sl.getInfo(inf);

    std::cout << "EngineVersion: " << inf.EngineVersion << std::endl;
    std::cout << "CriteriaVersion: " << inf.CriteriaVersion << std::endl;

    return 0;
}