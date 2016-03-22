//
// Created by burso on 3/20/16.
//

#include <iostream>
#include <vector>
#include <ssllabs/ssllabs.h>

int main() {
    SSLlabs sl;
    labsReport_t rpt;

    if (sl.analyze("ssllabs.com", rpt) != 0) {
        return 1;
    }

    std::cout << "Host: " << rpt.Host << std::endl;
    std::cout << "Port: " << rpt.Port << std::endl;
    std::cout << "Status: " << rpt.Status << std::endl;
    std::cout << "EngineVersion: " << rpt.EngineVersion << std::endl;
    std::cout << "CriteriaVersion: " << rpt.CriteriaVersion << std::endl;

    return 0;
}