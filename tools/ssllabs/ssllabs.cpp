#include <iostream>
#include <string>
#include "../../include/ssllabs/ssllabs.h"

using namespace ssllabs;

int main(int argc, char** argv) {
    ssllabs::SSLlabs ssllabsObject;
    std::string data;
    labsReport_t report;

    ssllabsObject.analyze("www.google.com", report);
    std::cout << "HOST: " << report.Host << "\n";
    std::cout << "PORT: " << report.Port << "\n";
    std::cout << "PROTOCOL: " << report.Protocol << "\n";
    std::cout << "isPublic: " << report.IsPublic << "\n";
    std::cout << "STATUS: " << report.Status << "\n";
    std::cout << "STARTTIME: " << report.StartTime << "\n";
    std::cout << "TESTTIME: " << report.TestTime << "\n";
    std::cout << "ENGINE VERSION: " << report.EngineVersion << "\n";
    std::cout << "CRITERIA VERSION: " << report.CriteriaVersion << "\n";

    std::vector<labsEndpoint_t>::iterator it;
    int counter = 1;
    for (it = report.Endpoints.begin(); it != report.Endpoints.end(); it++) {
        std::cout << "ENDPOINT " << counter << "\n";
        labsEndpoint_t endpoint;
        ssllabsObject.getEndpointData("www.google.com", it->IpAddress, endpoint);
        std::cout << "\tIP ADDRESS: " << endpoint.IpAddress << "\n";
        std::cout << "\tSERVER NAME: " << endpoint.ServerName << "\n";
        std::cout << "\tSTATUS MESSAGE: " << endpoint.StatusMessage << "\n";
        std::cout << "\tGRADE: " << endpoint.Grade << "\n";
        std::cout << "\tGRADE TRUST IGNORED: " << endpoint.GradeTrustIgnored << "\n";
        std::cout << "\tHAS WARNINGS: " << endpoint.HasWarnings << "\n";
        std::cout << "\tISEXCEPTIONAL: " << endpoint.IsExceptional << "\n";
        std::cout << "\tPROGRESS: " << endpoint.Progress << "\n";
        std::cout << "\tDURATION: " << endpoint.Duration << "\n";
        std::cout << "\tETA: " << endpoint.Eta << "\n";
        std::cout << "\tDELEGATION: " << endpoint.Delegation << "\n";

        std::cout << "\t\tHOST START TIME: " << endpoint.Details.HostStartTime << "\n";
        std::cout << "\t\tKEY INFORMATION\n";
        std::cout << "\t\t\tSIZE: " << endpoint.Details.Key.Size << "\n";
        std::cout << "\t\t\tALGORTIHM: " << endpoint.Details.Key.Algorithm << "\n";
        std::cout << "\t\t\tDEBIAN FLAW: " << endpoint.Details.Key.DebianFlaw << "\n";
        std::cout << "\t\t\tSTRENGTH: " << endpoint.Details.Key.Strength << "\n";
        std::cout << "\t\t\tQ: " << endpoint.Details.Key.Q << "\n";
        counter++;
    }
    return 0;
}
