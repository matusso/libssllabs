//
// Created by burso on 3/20/16.
//

#include <iostream>
#include <vector>
#include <ssllabs/ssllabs.h>

int main() {
    SSLlabs sl;
    labsInfo_t inf;

    sl.getInfo(inf);

    std::cout << "EngineVersion: " << inf.EngineVersion << std::endl;
    std::cout << "CriteriaVersion: " << inf.CriteriaVersion << std::endl;
    std::cout << "CurrentAssessments: " << inf.CurrentAssessments << std::endl;
    std::cout << "MaxAssessments: " << inf.MaxAssessments << std::endl;

    std::cout << "Messages: " << std::endl;
    for (std::vector<std::string>::iterator i = inf.Messages.begin(); i != inf.Messages.end(); i++) {
        std::cout << "\"" << i->c_str() << "\"" << std::endl;
    }

    return 0;
}