//
// Created by burso on 3/20/16.
//

#include <iostream>
#include <vector>
#include <ssllabs/ssllabs.h>

using namespace ssllabs;

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
    std::cout << "Endpoints: " << std::endl;

    for (auto i = rpt.Endpoints.begin(); i != rpt.Endpoints.end(); i++) {
        std::cout << "ipAddress: " << i->IpAddress << std::endl;
        std::cout << "grade: " << i->Grade << std::endl;
    }


    std::cout << std::endl << "Raw Data: " << rpt.RawJson << std::endl;


    return 0;
}